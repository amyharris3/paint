#pragma once

#include "GFX_Rectangle.h"
#include "WIN_Container.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

namespace win 
{
	class Layout;

	class Window : public Container
	{
	private:
		Layout  * layout_;
		gfx::Rectangle rect_;
		SDL_Renderer* renderer_;
		const char* name_;

		bool quit{ false };

	public:
		Window() = delete;
		virtual ~Window() = default;
		Window(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name);
		Window(Window const& that) = delete;
		Window(Window && that) = delete;
		Window & operator=(Window const& that) = delete;
		Window& operator=(Window && that) = delete;

		void draw() override;

	};
}
