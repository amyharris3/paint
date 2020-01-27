#include "WIN_ColourDisplay.h"
#include <SDL.h>

using namespace win;


ColourDisplay::ColourDisplay(gfx::Rectangle rect, const char* name, const std::shared_ptr<gfx::Colour> & displayColour, SDL_Renderer* renderer)
	: UIelement(rect, name)
	, displayColour_(displayColour)
	, renderer_(renderer)
{
	this->setForegroundColour(*displayColour);
	this->setBackgroundColour(gfx::Colour(0,0,0,255));

}

void ColourDisplay::updateColour()
{
	this->setForegroundColour(*displayColour_);
}

void ColourDisplay::setOutlineColour(const gfx::Colour outlineColour)
{
	this->setBackgroundColour(outlineColour);
}


void ColourDisplay::draw()
{
	SDL_Rect outlineRect = { this->getRect().x, this->getRect().y, this->getRect().width, this->getRect().height };
	uint8_t outlineColour[4];
	getBackgroundColour().getComponents(outlineColour);
	SDL_SetRenderDrawColor(renderer_, outlineColour[0], outlineColour[1], outlineColour[2], outlineColour[3]);
	SDL_RenderFillRect(renderer_, &outlineRect);

	SDL_Rect boxRect = { this->getRect().x+2, this->getRect().y+2, this->getRect().width-2, this->getRect().height -2 };
	uint8_t rgba[4];
	getForegroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);
}