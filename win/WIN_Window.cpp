#include "WIN_Window.h"
#include <SDL.h>

using namespace win;

Window::Window(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, gfx::Rectangle const& rect, const char* name)
	: Container(nullptr, rect, name)
	, layout_(nullptr)
	, rect_(rect)
	, sdlWindow_(sdlWindow)
	, renderer_(renderer)
	, name_(name)
	, surface_(surface)
{
}

Window::Window(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, gfx::Rectangle const & rect, const char* name, Layout* layout)
	: Container(nullptr, rect, name)
	, layout_(layout)
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
	auto colourArr = getBackgroundColour().getColour();
	SDL_SetRenderDrawColor(renderer_, colourArr[0], colourArr[1], colourArr[2], colourArr[3]);
	SDL_RenderFillRect(renderer_, &sdlRect);

	//if ((x != NULL) && (y != NULL)) {
	//	auto fgColourArr = getForegroundColour().getColour();
	//	SDL_SetRenderDrawColor(renderer_, fgColourArr[0], fgColourArr[1], fgColourArr[2], fgColourArr[3]);
	//	SDL_RenderDrawPoint(renderer_, x, y);
	//}

}


void Window::drawGenericBox(int x, int y, int width, int height, gfx::Colour boxColour)
{
	SDL_Rect sdlRect{ x, y, width, height };
	SDL_RenderDrawRect(renderer_, &sdlRect);
	auto colourArr = boxColour.getColour();
	SDL_SetRenderDrawColor(renderer_, colourArr[0], colourArr[1], colourArr[2], colourArr[3]);
	SDL_RenderFillRect(renderer_, &sdlRect);
}

/*void Window::drawLayout()
{
	gfx::Colour boxColour{ 50, 255, 255, 255 };

	//incorporate buttons here when they are finished
	for (auto element : layout_->getSubElements()) {
		drawGenericBox(element.xpos_, element.ypos_, layout_->getElementWidth(), layout_->getElementHeight(), boxColour);

	}
}
*/