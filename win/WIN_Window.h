#pragma once

#include "GFX_Rectangle.h"
#include "WIN_Container.h"
#include "WIN_FreeLayout.h"

//struct SDL_Window;
//struct SDL_Renderer;
//struct SDL_Surface;

namespace win 
{
	class Layout;
	class FreeLayout;
	class TableLayout;

	class Window : public Container
	{
	public:
		Window() = delete;
		virtual ~Window() = default;
		Window(const gfx::Rectangle& rect, const char* name);
		Window(const gfx::Rectangle& rect, const char* name, std::shared_ptr<Layout> layout);
		Window(Window const& that) = delete;
		Window(Window && that) = delete;
		Window & operator=(Window const& that) = delete;
		Window& operator=(Window && that) = delete;

		void draw(win::SDLRenderer* renderer) override;
		
	private:
		gfx::Rectangle rect_;

		void updateAndRerender(win::SDLRenderer* renderer) override;
	};
}
