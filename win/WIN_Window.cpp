#include "WIN_Window.h"
#include <SDL.h>

using namespace win;

Window::Window(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, gfx::Rectangle const & rect, const char* name)
	: Container(nullptr, rect, name)
	, layout_(nullptr)
	, rect_(rect)
	, sdlWindow_(sdlWindow)
	, renderer_(renderer)
	, name_(name)
	, surface_(surface)
{
}

void Window::draw()
{
	SDL_Rect sdlRect{ rect_.x, rect_.y, rect_.width, rect_.height };
	SDL_RenderDrawRect(renderer_, &sdlRect);
	uint8_t colourArr[4];
	getBackgroundColour().getComponents(colourArr);
	SDL_SetRenderDrawColor(renderer_, colourArr[0], colourArr[1], colourArr[2], colourArr[3]);
	SDL_RenderFillRect(renderer_, &sdlRect);

	//if ((x != NULL) && (y != NULL)) {
	//	auto fgColourArr = getForegroundColour().getColour();
	//	SDL_SetRenderDrawColor(renderer_, fgColourArr[0], fgColourArr[1], fgColourArr[2], fgColourArr[3]);
	//	SDL_RenderDrawPoint(renderer_, x, y);
	//}

}
