#include "WIN_pch.h"
#include "WIN_Slider.h"
#include "GFX_Renderer.h"

using namespace win;

Slider::Slider(gfx::Renderer* renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, int const initialPos, int const slideMin, int const slideMax)
	: UIelement(rect, name)
	, renderer_(renderer)
	, slideLineMin_(slideMin)
	, slideLineMax_(slideMax)
	, lineRect_(rect.x+2, int(rect.y+rect.height/2)-2, rect.width-5, 3)
	, lineColour_({0,0,0,255})
	, markerPos_(initialPos)
	, markerRect_(initialPos, rect.y, 5, rect.height)
	, markerColour_({ 0,0,0,255 })
	, holdMarker_(false)

{
	setForegroundColour(fillColour);
	setBackgroundColour(outlineColour);
}

void Slider::updateLineMarker()
{
	lineRect_ = gfx::Rectangle(getRect().x + 2, (getRect().y + getRect().height / 2) - 2, getRect().width - 5, 3);
	markerRect_ = gfx::Rectangle(markerPos_, getRect().y, 5, getRect().height);
}

void Slider::positionFromValue(int const val)
{
	markerPos_ = lineRect_.x +  int(double(val) * double(lineRect_.width) / (double(slideLineMax_) - double(slideLineMin_)));
	markerRect_.x = markerPos_;
}

// Need to convert scaling from the position
// subtracts 1 to deal with int/double/rounding errors that are introduced
int Slider::getValueFromPosition() const
{
	const auto relativeX = markerPos_ - lineRect_.x;
	return int(double(relativeX) * (double(slideLineMax_) - double(slideLineMin_)) / double(lineRect_.width));
}

void Slider::moveMarker()
{
	int xMouse = 0;
	int yMouse = 0;

	renderer_->getMouseState(xMouse, yMouse);
	
	if (xMouse > lineRect_.x + lineRect_.width - 2) {
		xMouse = lineRect_.x + lineRect_.width;
	}
	if (xMouse < lineRect_.x + 2) {
		xMouse = lineRect_.x;
	}
	markerRect_.x = xMouse;
	markerPos_ = xMouse;
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