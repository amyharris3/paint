#pragma once

#include "GFX_Rectangle.h"
#include "WIN_Container.h"
#include "WIN_FreeLayout.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

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
		Window(SDL_Window * sdlWindow, SDL_Renderer * renderer, SDL_Surface * surface, const gfx::Rectangle & rect, const char* name);
		Window(SDL_Window * sdlWindow, SDL_Renderer * renderer, SDL_Surface * surface, const gfx::Rectangle & rect, const char* name, std::shared_ptr<Layout> layout);
		Window(Window const& that) = delete;
		Window(Window && that) = delete;
		Window & operator=(Window const& that) = delete;
		Window& operator=(Window && that) = delete;

		void draw() override;

	protected:
		SDL_Window * getSDLWindow() { return sdlWindow_; }
		const SDL_Window * getSDLWindow() const { return sdlWindow_; }

	private:
		SDL_Window* sdlWindow_;
		SDL_Renderer* renderer_;
		// TODO SDL_Surface* surface_;
	};
}
