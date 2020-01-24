#pragma once
#include "WIN_Window.h"

namespace paint 
{
	//class Layout;

	class ToolWindow :
		public win::Window
	{
	public:
		ToolWindow(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, const gfx::Rectangle& rect, const char* name);
		ToolWindow(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, const gfx::Rectangle& rect, const char* name, std::shared_ptr<win::Layout> layout);
		virtual ~ToolWindow();

		void draw() override;

	};
}

