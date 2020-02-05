#pragma once
#include "WIN_Window.h"

namespace paint {
	class MenuWindow :
		public win::Window
	{
	public:
		MenuWindow() = delete;
		MenuWindow(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name);
		virtual ~MenuWindow() = default;
		MenuWindow(const MenuWindow& that) = delete;
		MenuWindow(MenuWindow&& that) = delete;
		MenuWindow& operator=(const MenuWindow& that) = delete;
		MenuWindow& operator=(MenuWindow&& that) = delete;
	};

}

