#include "PAINT_ToolWindow.h"

using namespace paint;

ToolWindow::ToolWindow(SDL_Window * sdlWindow, SDL_Renderer * renderer, SDL_Surface* surface, gfx::Rectangle const & rect, const char* name)
	: Window(sdlWindow, renderer, surface, rect, name)
{
}


ToolWindow::~ToolWindow()
{
}
