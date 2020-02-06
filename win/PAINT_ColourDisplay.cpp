#include "PAINT_ColourDisplay.h"
#include "../paint/PAINT_Utils.h"

using namespace paint;


ColourDisplay::ColourDisplay(gfx::Rectangle rect, const char* name, uint8_t displayColour[], gfx::Renderer* renderer, bool isActive)
	: UIelement(rect, name)
	, renderer_(renderer)
	, isActive_(isActive)
	, isClicked_(false)
{
	this->setForegroundColour(gfx::Colour(displayColour[0], displayColour[1], displayColour[2], displayColour[3]));
	if (isActive_)
	{
		this->setBackgroundColour(gfx::Colour(0, 0, 0, 255));
	}
	else
	{
		this->setBackgroundColour(gfx::Colour(200, 200, 200, 200));
	}
}

void ColourDisplay::setColour(const gfx::Colour colour)
{
	setForegroundColour(colour);
}

void ColourDisplay::setOutlineColour(const gfx::Colour outlineColour)
{
	this->setBackgroundColour(outlineColour);
}

void ColourDisplay::setActive()
{
	isActive_ = true;
	setBackgroundColour(gfx::Colour(0, 0, 0, 255));
}

void ColourDisplay::setInactive()
{
	isActive_ = false;
	setBackgroundColour(gfx::Colour(200, 200, 200, 200));
}

void ColourDisplay::swapIsActive()
{
	if (isActive_){
		setInactive();
	}
	else {
		setActive();
	}
}

void ColourDisplay::update()
{
	
}

void ColourDisplay::draw()
{
	renderer_->renderBox(getRect(), getBackgroundColour());
	renderer_->renderBox({ getRect().x + 5, getRect().y + 5, getRect().width - 10, getRect().height - 10 }, getForegroundColour());
	
	/*SDL_Rect outlineRect = { this->getRect().x, this->getRect().y, this->getRect().width, this->getRect().height };
	uint8_t outlineColour[4];
	getBackgroundColour().getComponents(outlineColour);
	SDL_SetRenderDrawColor(renderer_, outlineColour[0], outlineColour[1], outlineColour[2], outlineColour[3]);
	SDL_RenderFillRect(renderer_, &outlineRect);

	SDL_Rect boxRect = { this->getRect().x+5, this->getRect().y+5, this->getRect().width-10, this->getRect().height -10 };
	uint8_t rgba[4];
	getForegroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);*/
}

bool ColourDisplay::mouseExit()
{
	isClicked_ = false;
	return false;
}
bool ColourDisplay::mouseButtonDown(win::MouseButton const button)
{
	isClicked_ = true;
	return false;
}

bool ColourDisplay::mouseButtonUp(win::MouseButton const button)
{
	if (isClicked_) {
		const auto cpick = paint::utils::findToolWindow(this)->getColourPicker();
		cpick->swapActiveColour();
		isClicked_ = false;
	}
	return true;
}