#include "PAINT_ToolWindow.h"

#include <utility>
#include "PAINT_ColourPicker.h"

using namespace paint;

ToolWindow::ToolWindow(gfx::Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name)
{
}

ToolWindow::ToolWindow(gfx::Renderer* renderer, gfx::Rectangle const& rect, const char* name, std::shared_ptr<win::Layout> const& layout)
	: Window(renderer, rect, name, layout)
	, colourPicker_(nullptr)
{
}

/*
ToolWindow::~ToolWindow()
{
}
*/

void ToolWindow::setToolbox(std::shared_ptr<win::Window> toolbox)
{
	toolbox_ = std::move(toolbox);
}

void ToolWindow::setColourPicker(std::shared_ptr<ColourPicker> cpick)
{
	colourPicker_ = std::move(cpick);
}

//Draw toolbar in NxM table layout
void ToolWindow::draw()
{
	Window::draw();
}
bool ToolWindow::mouseButtonDown(win::MouseButton const button)
{
	return false;
}