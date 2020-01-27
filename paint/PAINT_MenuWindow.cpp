#include "PAINT_MenuWindow.h"
#include "WIN_Window.h"
#include <SDL.h>

using namespace paint;
using namespace win;

MenuWindow::MenuWindow(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name)
	: Window(renderer, rect, name)
{

}
