#pragma once
#include "WIN_Window.h"

namespace paint {
	class MenuWindow :
		public win::Window
	{
	public:
		MenuWindow(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name);
		virtual ~MenuWindow() = default;
	};

}

