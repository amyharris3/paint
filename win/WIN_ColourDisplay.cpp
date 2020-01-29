#include "WIN_ColourDisplay.h"
#include <SDL.h>
#include <iostream>
#include "../paint/PAINT_Utils.h"
#include "../paint/PAINT_DrawWindow.h"

using namespace win;


ColourDisplay::ColourDisplay(gfx::Rectangle rect, const char* name, const std::shared_ptr<gfx::Colour> & displayColour, SDL_Renderer* renderer, bool isActive)
	: UIelement(rect, name)
	, renderer_(renderer)
	, isActive_(isActive)
	, isClicked_(false)
{
	this->setForegroundColour(*displayColour);
	if (isActive_)
	{
		this->setBackgroundColour(gfx::Colour(0, 0, 0, 255));
	}
	else
	{
		this->setBackgroundColour(gfx::Colour(200, 200, 200, 200));
	}
}

void ColourDisplay::updateColour(const gfx::Colour colour)
{
	this->setForegroundColour(colour);
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

void ColourDisplay::swapActive()
{
	if (isActive_){
		setInactive();
	}
	else {
		setActive();
	}
}

void ColourDisplay::setOutlineColour(const gfx::Colour outlineColour)
{
	//this->setBackgroundColour(outlineColour);
}

void ColourDisplay::draw()
{
	SDL_Rect outlineRect = { this->getRect().x, this->getRect().y, this->getRect().width, this->getRect().height };
	uint8_t outlineColour[4];
	getBackgroundColour().getComponents(outlineColour);
	SDL_SetRenderDrawColor(renderer_, outlineColour[0], outlineColour[1], outlineColour[2], outlineColour[3]);
	SDL_RenderFillRect(renderer_, &outlineRect);

	SDL_Rect boxRect = { this->getRect().x+5, this->getRect().y+5, this->getRect().width-10, this->getRect().height -10 };
	uint8_t rgba[4];
	getForegroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);
}

void ColourDisplay::mouseButtonDown(win::MouseButton const button)
{
	isClicked_ = true;
}

void ColourDisplay::mouseButtonUp(win::MouseButton const button)
{
	auto cpick = paint::utils::findToolWindow(this)->getColourPicker();
	cpick->swapActiveColour();
	
	isClicked_ = false;
}