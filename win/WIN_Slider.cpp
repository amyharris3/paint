#include "WIN_Slider.h"
#include "GFX_Renderer.h"

using namespace win;

//Demanding minimum dimensions for the slider box, if input parameters are below the minimum size then it will re-adjust
Slider::Slider(gfx::Renderer* renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, int const initialVal, int const slideMin, int const slideMax)
	: UIelement(rect, name)
	, renderer_(renderer)
	, slideLineMin_(slideMin)
	, slideLineMax_(slideMax)
	, lineRect_(rect.x+2, int(rect.y+rect.height/2)-2, rect.width-5, 3)
	, lineColour_({0,0,0,255})
	, markerVal_(initialVal)
	, markerRect_(getPositionFromValue(), rect.y, 5, rect.height)
	, markerColour_({ 0,0,0,255 })
	, holdMarker_(false)

{
	setForegroundColour(fillColour);
	setBackgroundColour(outlineColour);

	//accounting for ridiculously tiny boxes that shouldn't be used
	if(rect.width < 5){
		lineRect_.x = rect.x;
		lineRect_.width = rect.width;
		markerRect_.x = getPositionFromValue();
		markerRect_.width = 1;
	}
	if(rect.height < 3 ){
		lineRect_.y = rect.y;
		lineRect_.height = 1;
	}
	
}

//Good to call this to automatically scale if the dimensions of the slider rect have been changed
void Slider::updateLineMarker()
{
	lineRect_ = gfx::Rectangle(getRect().x + 2, (getRect().y + getRect().height / 2) - 2, getRect().width - 5, 3);
	markerRect_ = gfx::Rectangle(getPositionFromValue(), getRect().y, 5, getRect().height);
}
int Slider::getPositionFromValue() const
{
	return lineRect_.x + static_cast<int>(round((static_cast<double>(markerVal_) * static_cast<double>(lineRect_.width) / (static_cast<double>(slideLineMax_) - static_cast<double>(slideLineMin_)))));
}

// Need to convert scaling from the position
// subtracts 1 to deal with int/double/rounding errors that are introduced
int Slider::getValueFromPosition() const
{
	const auto relativeX = markerRect_.x - lineRect_.x;
	//return relativeX * int(round((double(slideLineMax_) - double(slideLineMin_)) / double(lineRect_.width)));
	return static_cast<int>(round(static_cast<double>(relativeX) *(static_cast<double>(slideLineMax_) - static_cast<double>(slideLineMin_)) / static_cast<double>(lineRect_.width))) - 1;
}

//When changing marker value or position, always want to change the other at the same time, don't let them get out of sync
void Slider::setMarkerValue(int val)
{
	if (val > slideLineMax_){
		val = slideLineMax_;
	}
	else if (val < slideLineMin_){
		val = slideLineMin_;
	}
	markerVal_ = val;

	auto x = getPositionFromValue();
	if (x > lineRect_.x + lineRect_.width - 2) {
		x = lineRect_.x + lineRect_.width;
	}
	else if (x < lineRect_.x + 2) {
		x = lineRect_.x;
	}
	markerRect_.x = x;
}

// marker position is absolute relative to the global (x,y) scale
// Should be within range of rectangle, else set to range
void Slider::setMarkerPos(int x)
{
	if (x > lineRect_.x + lineRect_.width - 2) {
		x = lineRect_.x + lineRect_.width;
	}
	else if (x < lineRect_.x + 2) {
		x = lineRect_.x;
	}
	markerRect_.x = x;

	auto val = getValueFromPosition();
	if (val > slideLineMax_) {
		val = slideLineMax_;
	}
	else if (val < slideLineMin_) {
		val = slideLineMin_;
	}
	markerVal_ = val;
}

void Slider::moveMarker()
{
	int xMouse = 0;
	int yMouse = 0;

	renderer_->getMouseState(xMouse, yMouse);

	setMarkerPos(xMouse);
}

void Slider::update()
{
	updateLineMarker();
}


void Slider::updateAndRerender()
{
	updateLineMarker();
	
	draw();
	renderer_->renderPresent();
}

void Slider::draw()
{
	//updateLineMarker();
	
	renderer_->renderBox(getRect(), getForegroundColour());
	renderer_->renderBox(lineRect_, lineColour_);
	renderer_->renderBox({ markerRect_.x - 2, markerRect_.y, markerRect_.width, markerRect_.height }, markerColour_);

	/*SDL_Rect boxRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	getForegroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);

	SDL_Rect lineRect = { lineRect_.x, lineRect_.y, lineRect_.width, lineRect_.height };
	lineColour_.getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &lineRect);

	SDL_Rect markerRect = { markerRect_.x-2, markerRect_.y, markerRect_.width, markerRect_.height };
	markerColour_.getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &markerRect);*/

}

bool Slider::mouseExit()
{
	holdMarker_ = false;
	return false;
}

bool Slider::mouseMove()
{
	if (holdMarker_) {
		moveMarker();
		//updateAndRerender();
	}
	return true;
}

bool Slider::mouseButtonDown(MouseButton button)
{
	holdMarker_ = true;
	return false;
}

bool Slider::mouseButtonUp(MouseButton button)
{
	if (holdMarker_== true){
		int xMouse = 0;
		int yMouse = 0;
		
		SDL_GetMouseState(&xMouse, &yMouse);
		markerRect_.x = xMouse;
		//updateAndRerender();
	}
	
	holdMarker_ = false;
	return true;
}