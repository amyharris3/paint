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
		const char* name_;  
		gfx::Colour primaryColour_;
		gfx::Colour secondaryColour_;
		std::vector<Coords> clickedPixels_;  
		SDL_Surface* surface_;
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		bool drawToggle_;
//


	public:
		DrawWindow() = delete;
		DrawWindow(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name);

		virtual ~DrawWindow();
		DrawWindow(const DrawWindow& that) = delete;
		DrawWindow(DrawWindow&& that) = delete;
		DrawWindow& operator=(const DrawWindow& that) = delete;
		DrawWindow& operator=(DrawWindow&& that) = delete;

		void mouseButtonDown(win::MouseButton button, int xPixel, int yPixel) override;
		void setActiveBrush(Brush* brush);
		//void getPixels(SDL_Surface* surface);

		gfx::Colour getPrimaryColour() const { return primaryColour_; }
		gfx::Colour getSecondaryColour() const { return secondaryColour_; }
		void setPrimaryColour(gfx::Colour colour);
		void setSecondaryColour(gfx::Colour colour);
		void swapColours();

		//void setColor(SDL_Surface* surface);
		void draw() override;
		void toggleDraw();
	};
}