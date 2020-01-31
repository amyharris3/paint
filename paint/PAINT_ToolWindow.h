#pragma once
#include "WIN_Window.h"

namespace paint {
	class ToolWindow final :
		public win::Window
	{
	public:
		ToolWindow(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name, std::shared_ptr<win::Layout> const & layout);
		ToolWindow(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name);
		virtual ~ToolWindow() = default;
		ToolWindow(const ToolWindow& that) = delete;
		ToolWindow(ToolWindow&& that) = delete;
		ToolWindow& operator=(const ToolWindow& that) = delete;
		ToolWindow& operator=(ToolWindow&& that) = delete;
		
		void draw() override;
		
	};
}

