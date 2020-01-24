#pragma once

#include "WIN_Window.h"
#include "GFX_Colour.h"

namespace paint
{
	class StatusBarWindow :
		public win::Window
	{
	public:
		StatusBarWindow() = default;
		StatusBarWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name);
		void displayMouseCoords(int xMouse, int yMouse);
		virtual ~StatusBarWindow() = default;
	};
}
