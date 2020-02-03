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
	// TODO , surface_(surface)
{
}

void Window::updateAndRerender()
{
	for (const auto& child : getChildren()){
		child->update();
		child->draw();
		SDL_RenderPresent(renderer_);
	}
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