#include "WIN_GenericBox.h"
#include <SDL.h>

using namespace win;

GenericBox::GenericBox(gfx::Rectangle& rect, const char* name, gfx::Colour foregroundColour, gfx::Colour backgroundColour, SDL_Renderer* renderer)
	: UIelement(rect, name)
	, renderer_(renderer)
{
	this->setForegroundColour(foregroundColour);
	this->setBackgroundColour(backgroundColour);

	//boxRect_ = { this->getRect().x, this->getRect().y, this->getRect().width, this->getRect().height };
}

void GenericBox::draw()
{
	SDL_Rect boxRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	uint8_t rgba[4];
	getBackgroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);
}