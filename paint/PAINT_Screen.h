#pragma once
#include "WIN_Container.h"

struct SDL_Renderer;

namespace paint {

	class DrawWindow;
	class ToolWindow;
	class StatusBarWindow;
	class MenuWindow;

	class Screen final :
		public win::Container
	{
	public:
		Screen() = default;
		Screen(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name);
		~Screen() = default;
		Screen(Screen const& that) = default;
		Screen(Screen&& that) = default;
		Screen& operator=(Screen const& that) = default;
		Screen& operator=(Screen&& that) = default;

		DrawWindow* getDrawWindow() const { return drawWindow_.get(); }
		ToolWindow* getToolWindow() const { return toolWindow_.get(); }

	private:
		std::shared_ptr<DrawWindow> drawWindow_;
		std::shared_ptr<ToolWindow> toolWindow_;

	};
}