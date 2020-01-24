#pragma once

#include "WIN_Window.h"

struct SDL_Texture;

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

	class Colour;
	class Tool;
	class Brush;

	class DrawWindow :
		public win::Window
	{
	private:
		// TODO What sort of pointer?
		Tool * activeTool_;
		Brush * activeBrush_;
		const char* name_;
		std::vector<Coords> clickedPixels_;  
		SDL_Surface* surface_;
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		bool drawingToggle_;
//


	public:
		DrawWindow() = default;
		DrawWindow(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, const gfx::Rectangle& rect, const char* name);

		virtual ~DrawWindow();

		void AddClickedPixels(int xMouse, int yMouse);
		void mouseButtonDown(win::MouseButton button, int xPixel, int yPixel) override;
		void setActiveBrush(Brush* brush);
		//void getPixels(SDL_Surface* surface);
		void changeDrawToggle(bool drawingToggle) { drawingToggle_ = drawingToggle; }

		//void setColor(SDL_Surface* surface);
		void draw() override;
	};
}