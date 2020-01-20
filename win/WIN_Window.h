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
		SDL_Window* sdlWindow_;
		SDL_Renderer* renderer_;
		SDL_Surface* surface_;
		const char* name_;

		bool quit{ false };

	public:
		Window() = delete;
		virtual ~Window() = default;
		Window(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, const gfx::Rectangle& rect, const char* name);
		Window(Window const& that) = delete;
		Window(Window && that) = delete;
		Window & operator=(Window const& that) = delete;
		Window& operator=(Window && that) = delete;

		void draw() override;

	protected:
		SDL_Window * getSDLWindow() { return sdlWindow_; }
		const SDL_Window * getSDLWindow() const { return sdlWindow_; }
	};
}
