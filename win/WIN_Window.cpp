#include "WIN_pch.h"
#include "WIN_Window.h"
#include "WIN_FreeLayout.h"

using namespace win;

// If initialised without a layout, defaults to FreeLayout
Window::Window(gfx::Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name, std::make_shared<FreeLayout>())
{
}

Window::Window(gfx::Renderer* renderer, gfx::Rectangle const& rect, const char* name, std::shared_ptr<Layout> layout)
	: Container(std::move(layout), rect, name)
	, renderer_(renderer)
{
}

void Window::updateAndRerender()
{
	for (const auto& child : getChildren()){
		child->update();
		child->draw();
		getRenderer()->renderPresentScreen();
	}
}

void Window::draw()
{
	getRenderer()->renderBox(gfx::RenderTarget::SCREEN, getRect(), getBackgroundColour());
	
	Container::draw();

}