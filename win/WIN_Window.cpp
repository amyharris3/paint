#include "WIN_pch.h"
#include "WIN_Window.h"
#include "WIN_FreeLayout.h"

using namespace win;

// If initialised without a layout, defaults to FreeLayout
Window::Window(gfx::Rectangle const& rect, const char* name)
	: Window(rect, name, std::make_shared<FreeLayout>())
{
}

Window::Window(gfx::Rectangle const& rect, const char* name, std::shared_ptr<Layout> layout)
	: Container(std::move(layout), rect, name)
{
}

void Window::updateAndRerender(win::SDLRenderer* renderer)
{
	for (const auto& child : getChildren()){
		child->update();
		child->draw(renderer);
		renderer->renderPresentScreen();
	}
}

void Window::draw(win::SDLRenderer* renderer)
{
	renderer->renderBox(gfx::RenderTarget::SCREEN, getRect(), getBackgroundColour());
	
	Container::draw(renderer);

}