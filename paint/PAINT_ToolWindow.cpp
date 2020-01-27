#include "PAINT_ToolWindow.h"
#include "PAINT_ColourPicker.h"

using namespace paint;

ToolWindow::ToolWindow(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, gfx::Rectangle const& rect, const char* name)
	: Window(sdlWindow, renderer, surface, rect, name)
{
}

ToolWindow::ToolWindow(SDL_Window * sdlWindow, SDL_Renderer * renderer, SDL_Surface* surface, gfx::Rectangle const & rect, const char* name, std::shared_ptr<win::Layout> const & layout)
	: Window(sdlWindow, renderer, surface, rect, name, layout)
{
}

/*
ToolWindow::~ToolWindow()
{
}
*/

//Draw toolbar in NxM table layout
void ToolWindow::draw()
{
	Window::draw();
}

void ToolWindow::mouseButtonDown(win::MouseButton const b, int const xPixel, int const yPixel)
{
	
}