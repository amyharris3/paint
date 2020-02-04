#include "WIN_Window.h"
#include <SDL.h>
#include "WIN_FreeLayout.h"

using namespace win;

// If initialised without a layout, defaults to FreeLayout
Window::Window(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name, std::make_shared<FreeLayout>())
{
}

Window::Window(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name, std::shared_ptr<Layout> layout)
	: Container(std::move(layout), rect, name)
	, renderer_(renderer)
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

}