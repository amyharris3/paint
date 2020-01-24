#include "WIN_Window.h"
#include <SDL.h>
#include "WIN_FreeLayout.h"

using namespace win;

// If initialised without a layout, defaults to FreeLayout
Window::Window(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, gfx::Rectangle const& rect, const char* name)
: Window(sdlWindow, renderer, surface, rect, name, std::make_shared<FreeLayout>())
{
}

Window::Window(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, gfx::Rectangle const & rect, const char* name, std::shared_ptr<Layout> layout)
	: Container(std::move(layout), rect, name)
	, sdlWindow_(sdlWindow)
	, renderer_(renderer)
	// TODO , surface_(surface)
{
}

void Window::draw()
{
	const auto& rect = getRect();
	SDL_Rect sdlRect{ rect.x, rect.y, rect.width, rect.height };
	SDL_RenderDrawRect(renderer_, &sdlRect);
	uint8_t rgba[4];
	getBackgroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &sdlRect);
	Container::draw();

	//if ((x != NULL) && (y != NULL)) {
	//	auto fgColourArr = getForegroundColour().getColour();
	//	SDL_SetRenderDrawColor(renderer_, fgColourArr[0], fgColourArr[1], fgColourArr[2], fgColourArr[3]);
	//	SDL_RenderDrawPoint(renderer_, x, y);
	//}

}