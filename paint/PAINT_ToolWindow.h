#pragma once
#include "WIN_Window.h"

namespace paint 
{
	class ToolWindow :
		public win::Window
	{
	public:
		ToolWindow(SDL_Window * sdlWindow, SDL_Renderer * renderer, SDL_Surface* surface, const gfx::Rectangle & rect, const char* name);
		virtual ~ToolWindow();

	};
}

