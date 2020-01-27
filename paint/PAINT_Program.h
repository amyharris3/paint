#pragma once

#include "WIN_Container.h"
#include "PAINT_Screen.h"


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

namespace paint
{
	class DrawWindow;
	class ToolWindow;
	class Screen;
	//class StatusBarWindow;


	
	class Program
	{
	private:
		std::shared_ptr<Screen> screen_;
		//win::Container screen_;
		SDL_Renderer* renderer_;
		//std::shared_ptr<DrawWindow> drawWindow_;
		//std::shared_ptr<ToolWindow> toolWindow_;
		
		//ToolWindow * toolWindow_;
		//StatusBarWindow * statusWindow_;
		
		bool quit;

	public:
		Program() = default;
		~Program() = default;
		Program(Program const& that) = default;
		Program(Program&& that) = default;
		Program& operator=(Program const& that) = default;
		Program& operator=(Program&& that) = default;


		void initialize(SDL_Renderer* renderer);
		void run();

	
	};
}
