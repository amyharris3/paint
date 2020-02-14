#include "PAINT_pch.h"
#include "PAINT_ToolWindow.h"

#include <utility>
#include "PAINT_ColourPicker.h"

using namespace paint;

ToolWindow::ToolWindow(gfx::Rectangle const& rect, const char* name)
	: Window(rect, name)
{
}

ToolWindow::ToolWindow(gfx::Rectangle const& rect, const char* name, std::shared_ptr<win::Layout> const& layout)
	: Window(rect, name, layout)
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

void ToolWindow::setThicknessButtonGroup(std::shared_ptr<win::ButtonGroup> buttonGroup)
{
	thicknessButtonGroup_ = std::move(buttonGroup);
}

//Draw toolbar in NxM table layout
void ToolWindow::draw(win::SDLRenderer* renderer)
{
	Window::draw(renderer);
}

bool ToolWindow::mouseButtonDown(win::MouseButton button, bool clicked)
{
	return false;
}