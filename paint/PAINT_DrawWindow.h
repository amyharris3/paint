#pragma once

#include "WIN_Window.h"

struct SDL_Texture;

namespace gfx
{
	class Colour;
}

namespace win
{
	enum class MouseButton;
}

namespace paint 
{
	// JG: Coords.h? Vector2.h? 
	struct Coords
	{
		int x;
		int y;
	};

	class Tool;
	class Brush;

	class DrawWindow final :
		public win::Window
	{
	private:
		// TODO What sort of pointer?
		Tool * activeTool_;
		Brush * activeBrush_;
		gfx::Colour activeColour_;
		gfx::Colour inactiveColour_;
		std::vector<Coords> clickedPixels_;  
		SDL_Surface* surface_;
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
//


	public:
		DrawWindow() = delete;
		DrawWindow(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, const gfx::Rectangle& rect, const char* name);

		virtual ~DrawWindow();
		DrawWindow(const DrawWindow& that) = delete;
		DrawWindow(DrawWindow&& that) = delete;
		DrawWindow& operator=(const DrawWindow& that) = delete;
		DrawWindow& operator=(DrawWindow&& that) = delete;


		void addClickedPixels(int xMouse, int yMouse);
		void mouseButtonDown(win::MouseButton b, int xPixel, int yPixel) override;
		void setActiveBrush(Brush* brush);
		//void getPixels(SDL_Surface* surface);

		void swapActiveColour();

		//void setColor(SDL_Surface* surface);
		void draw() override;
	};
}