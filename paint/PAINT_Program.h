#pragma once

#include <WIN_Container.h>


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

namespace paint
{
	class DrawWindow;
	//class ToolWindow;
	//class StatusBarWindow;

	class Program
	{
	private:
		win::Container screen_;
		SDL_Window* window_;
		SDL_Renderer* renderer_;
		SDL_Surface* surface_;
		SDL_Texture* texture_;
		std::shared_ptr<DrawWindow> drawWindow_;
		//ToolWindow * toolWindow_;
		//StatusBarWindow * statusWindow_;
		
		//bool quit;

	public:
		Program();
		~Program() = default;
		Program(Program const& that) = default;
		Program(Program&& that) = default;
		Program& operator=(Program const& that) = default;
		Program& operator=(Program&& that) = default;


		void initialize(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture);
		void run();

	};
}
