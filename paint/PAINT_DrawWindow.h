#pragma once

#include "WIN_Window.h"
#include "PAINT_ColourPicker.h"

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

	struct Line
	{
		int x1;
		int y1;
		int x2;
		int y2;

	};

	class Colour;
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
		Coords mouseCoords_;
		Coords prevMouseCoords_;
		std::vector<Line> lines_;

		//whenever the active colour is changed this should be updated
		uint8_t rgbaDrawColour_[4]; 

	public:
		DrawWindow() = delete;
		DrawWindow(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name);

		virtual ~DrawWindow();
		DrawWindow(const DrawWindow& that) = delete;
		DrawWindow(DrawWindow&& that) = delete;
		DrawWindow& operator=(const DrawWindow& that) = delete;
		DrawWindow& operator=(DrawWindow&& that) = delete;
	
		void mouseButtonDown(win::MouseButton button) override;
		void setActiveBrush(Brush* brush);
		//void getPixels(SDL_Surface* surface);
		void setMouseCoords(Coords relCoords);
		Coords getMouseCoords() const { return mouseCoords_; }
		void setPrevCoords(Coords relPrevCoords);

		gfx::Colour getPrimaryColour() const { return primaryColour_; }
		gfx::Colour getSecondaryColour() const { return secondaryColour_; }
		void setPrimaryColour(gfx::Colour colour);
		void setSecondaryColour(gfx::Colour colour);
		void swapColours();
		void setDrawColourPrimary();
		void setDrawColourSecondary();

		//void setColor(SDL_Surface* surface);
		void draw() override;
		void toggleDraw();
	};
}