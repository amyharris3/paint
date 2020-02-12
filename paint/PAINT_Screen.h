#pragma once
#include "WIN_Container.h"

namespace win {
	class SDLRenderer;
}

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
		Screen(win::SDLRenderer* renderer, const gfx::Rectangle& rect, const char* name);
		~Screen() = default;
		Screen(Screen const& that) = default;
		Screen(Screen&& that) = default;
		Screen& operator=(Screen const& that) = default;
		Screen& operator=(Screen&& that) = default;

		DrawWindow* getDrawWindow() const { return drawWindow_.get(); }
		ToolWindow* getToolWindow() const { return toolWindow_.get(); }
		StatusBarWindow* getStatusBarWindow() const { return statusBarWindow_.get(); }

		void updateAndRerender(win::SDLRenderer* renderer) override;
	private:
		std::shared_ptr<DrawWindow> drawWindow_;
		std::shared_ptr<ToolWindow> toolWindow_;
		std::shared_ptr<StatusBarWindow> statusBarWindow_;
		
	};
}