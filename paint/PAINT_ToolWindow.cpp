#include "PAINT_ToolWindow.h"

using namespace paint;

ToolWindow::ToolWindow(SDL_Renderer * renderer, gfx::Rectangle const & rect, const char* name)
	: Window(renderer, rect, name)
{
}


ToolWindow::~ToolWindow()
{
}

//
//void ToolWindow::draw()
//{
//
//	for (auto child : this->getChildren()) {
//		child->draw();
//	}
//}