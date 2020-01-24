#pragma once
#include "WIN_Window.h"

namespace paint {
	class ToolWindow :
		public win::Window
	{
	public:
		ToolWindow(SDL_Renderer * renderer, const gfx::Rectangle & rect, const char* name);
		virtual ~ToolWindow();

		//void draw() override;

	};
}

