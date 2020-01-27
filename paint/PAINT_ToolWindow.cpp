#include "PAINT_ToolWindow.h"
#include "PAINT_ColourPicker.h"

using namespace paint;

ToolWindow::ToolWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name)
{
}

ToolWindow::ToolWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name, std::shared_ptr<win::Layout> const& layout)
	: Window(renderer, rect, name, layout)
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

void ToolWindow::mouseButtonDown(win::MouseButton const b)
{

}