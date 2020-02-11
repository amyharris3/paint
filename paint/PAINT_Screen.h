#pragma once
#include "WIN_Container.h"

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

	};

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

		void updateAndRerender() override;
	private:
		std::shared_ptr<DrawWindow> drawWindow_;
		std::shared_ptr<ToolWindow> toolWindow_;

	};
}