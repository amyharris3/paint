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

	class Tool;
	class Brush;

	class DrawWindow final :
		public win::Window
	{

	public:
		DrawWindow() = delete;
		DrawWindow(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name);

		virtual ~DrawWindow();
		DrawWindow(const DrawWindow& that) = delete;
		DrawWindow(DrawWindow&& that) = delete;
		DrawWindow& operator=(const DrawWindow& that) = delete;
		DrawWindow& operator=(DrawWindow&& that) = delete;
	
		bool mouseButtonDown(win::MouseButton button) override;
		
		void setActiveBrush(Brush* brush);
		//void getPixels(SDL_Surface* surface);
		void setMouseCoords(Coords relCoords);
		Coords getMouseCoords() const { return mouseCoords_; }
		void setPrevCoords(Coords relPrevCoords);

		gfx::Colour getPrimaryColour() const { return primaryColour_; }
		gfx::Colour getSecondaryColour() const { return secondaryColour_; }
		void setPrimaryColour(gfx::Colour colour);
		void setSecondaryColour(gfx::Colour colour);
		void swapPrimarySecondaryColours();

		uint8_t* getDrawRGBA() { return drawRGBA_; }
		uint8_t* getDrawRed() { return &drawRGBA_[0]; }
		uint8_t* getDrawGreen() { return &drawRGBA_[1]; }
		uint8_t* getDrawBlue() { return &drawRGBA_[2]; }
		uint8_t* getDrawAlpha() { return &drawRGBA_[3]; }
		
		uint8_t* getPrimaryRGBA() { return primaryRGBA_; }
		uint8_t* getPrimaryRed() { return &primaryRGBA_[0]; }
		uint8_t* getPrimaryGreen() { return &primaryRGBA_[1]; }
		uint8_t* getPrimaryBlue() { return &primaryRGBA_[2]; }
		uint8_t* getPrimaryAlpha() { return &primaryRGBA_[3]; }

		uint8_t* getSecondaryRGBA() { return secondaryRGBA_; }
		uint8_t* getSecondaryRed() { return &secondaryRGBA_[0]; }
		uint8_t* getSecondaryGreen() { return &secondaryRGBA_[1]; }
		uint8_t* getSecondaryBlue() { return &secondaryRGBA_[2]; }
		uint8_t* getSecondaryAlpha() { return &secondaryRGBA_[3]; }
	
		void setDrawColourAsPrimary();
		void setDrawColourAsSecondary();
		void setPrimaryAsDrawColour();
		void setSecondaryAsDrawColour();

		//void setColor(SDL_Surface* surface);
		void draw() override;
		void toggleDraw();
		void clearScreen() const;

	private:
		// TODO What sort of pointer?
		Tool* activeTool_;
		Brush* activeBrush_;
		//const char* name_;
		gfx::Colour primaryColour_;
		gfx::Colour secondaryColour_;
		std::vector<Coords> clickedPixels_;
		//SDL_Surface* surface_;
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		bool drawToggle_;
		Coords mouseCoords_;
		Coords prevMouseCoords_;
		std::vector<Line> lines_;

		//whenever the active colour is changed this should be updated
		uint8_t drawRGBA_[4];
		uint8_t primaryRGBA_[4];
		uint8_t secondaryRGBA_[4];

	};
}