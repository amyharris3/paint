#include "PAINT_StatusBarWindow.h"

using namespace paint;

StatusBarWindow::StatusBarWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name)
{
}
