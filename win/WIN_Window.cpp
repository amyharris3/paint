#include "WIN_Window.h"
#include <SDL.h>
#include "WIN_FreeLayout.h"

using namespace win;

Window::Window(SDL_Renderer* renderer, gfx::Rectangle const & rect, const char* name)
	: Container(nullptr, rect, name)
	, layout_(nullptr)
	, rect_(rect)
	, renderer_(renderer)
	, name_(name)
{
}

void Window::draw()
{
	const auto& rect = getRect();
	SDL_Rect sdlRect{ rect.x, rect.y, rect.width, rect.height };
	SDL_RenderDrawRect(renderer_, &sdlRect);
	uint8_t colourArr[4];
	getBackgroundColour().getComponents(colourArr);
	SDL_SetRenderDrawColor(renderer_, colourArr[0], colourArr[1], colourArr[2], colourArr[3]);
	SDL_RenderFillRect(renderer_, &sdlRect);
	Container::draw();

	//if ((x != NULL) && (y != NULL)) {
	//	auto fgColourArr = getForegroundColour().getColour();
	//	SDL_SetRenderDrawColor(renderer_, fgColourArr[0], fgColourArr[1], fgColourArr[2], fgColourArr[3]);
	//	SDL_RenderDrawPoint(renderer_, x, y);
	//}

}