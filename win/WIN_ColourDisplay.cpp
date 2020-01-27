#include "WIN_ColourDisplay.h"
#include <SDL.h>
#include "WIN_Mouse.h"

using namespace win;


ColourDisplay::ColourDisplay(gfx::Rectangle rect, const char* name, const std::shared_ptr<gfx::Colour> & displayColour, SDL_Renderer* renderer, bool isActive)
	: UIelement(rect, name)
	, displayColour_(displayColour)
	, renderer_(renderer)
	, isActive_(isActive)
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

void ColourDisplay::updateColour()
{
	this->setForegroundColour(*displayColour_);
}

void ColourDisplay::setActive()
{
	this->setBackgroundColour(gfx::Colour(0, 0, 0, 255));
}

void ColourDisplay::setInactive()
{
	this->setBackgroundColour(gfx::Colour(200, 200, 200, 200));
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

void ColourDisplay::mouseButtonDown(win::MouseButton const b)
{
	
}