#pragma once
#include "WIN_Container.h"

namespace gfx {
	class Renderer;
}
struct SDL_Renderer;

namespace paint {

	class DrawWindow;
	class ToolWindow;
	class StatusBarWindow;
	class MenuWindow;

	struct ButtonInfo
	{
		const char* buttonName;
		const char* buttonSpritePath;
		win::UIelement::ActionFunction action;
		bool toggleType;

	};

	class Screen final :
		public win::Container
	{
	public:
		Screen() = default;
		Screen(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name);
		~Screen() = default;
		Screen(Screen const& that) = default;
		Screen(Screen&& that) = default;
		Screen& operator=(Screen const& that) = default;
		Screen& operator=(Screen&& that) = default;

		DrawWindow* getDrawWindow() const { return drawWindow_.get(); }
		ToolWindow* getToolWindow() const { return toolWindow_.get(); }
		StatusBarWindow* getStatusBarWindow() const { return statusBarWindow_.get(); }

		void updateAndRerender() override;
	private:
		std::shared_ptr<DrawWindow> drawWindow_;
		std::shared_ptr<ToolWindow> toolWindow_;
		std::shared_ptr<StatusBarWindow> statusBarWindow_;
		
	};
}