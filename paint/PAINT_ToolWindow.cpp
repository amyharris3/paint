#include "PAINT_pch.h"
#include "PAINT_ToolWindow.h"

#include <utility>
#include "PAINT_ColourPicker.h"

using namespace paint;

ToolWindow::ToolWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name)
{
}

ToolWindow::ToolWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name, std::shared_ptr<win::Layout> const& layout)
	: Window(renderer, rect, name, layout)
	, colourPicker_(nullptr)
{
}

void ToolWindow::setToolbox(std::shared_ptr<win::Window> toolbox)
{
	toolbox_ = std::move(toolbox);
}

void ToolWindow::setColourPicker(std::shared_ptr<ColourPicker> cPick)
{
	colourPicker_ = std::move(cPick);
}

//Draw toolbar in NxM table layout
void ToolWindow::draw()
{
	Window::draw();
}

bool ToolWindow::mouseButtonDown(win::MouseButton const)
{
	return false;
}