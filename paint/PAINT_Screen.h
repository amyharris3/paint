#pragma once
#include "WIN_Container.h"

namespace gfx {
	class Renderer;
}

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

namespace win {
	class Layout;
}

namespace paint {

	class DrawWindow;
	class ToolWindow;
	class StatusBarWindow;
	class MenuWindow;

	class Screen :
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

		void updateAndRerender() override;
		
		//void setDrawWindow(DrawWindow* drawWindow);
		//void setToolWindow(ToolWindow* toolWindow);


	private:
		std::shared_ptr<DrawWindow> drawWindow_;
		std::shared_ptr<ToolWindow> toolWindow_;
		std::shared_ptr<StatusBarWindow> statusWindow_;
		std::shared_ptr<MenuWindow> menuWindow_;


	};
}