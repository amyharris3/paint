#pragma once
#include "SDL.h"
#include <vector>
#include "GFX_Text.h"

namespace gfx
{
	class Colour;
	class Rectangle;
	class Line;

	// The purpose of the separate renderer class is to handle the SDL rendering, so as to allow the PAINT and WIN classes to function without needing to load SDL.
	// Will be dependent on all other classes as it needs to have the functionality to render each of them.
	// Default/empty constructor sets nullptr for the SDL renderer, use if necessary for unit testing, but do NOT use when actually rendering anything or it will cause assertion error.
	class Renderer
	{
	public:
		Renderer(); //should only be used in debug
		Renderer(SDL_Renderer* renderer);
		~Renderer();
		Renderer(const Renderer & that) = default;
		Renderer(Renderer && that) = default;
		Renderer& operator=(const Renderer & that) = default;
		Renderer& operator=(Renderer && that) = default;

		bool notDummy() const;
		
		SDL_Renderer* getRendererSDL() const { return rendererSDL_; }
		
		void createDrawWindowTexture(Rectangle rect);
		void destroyDrawWindowTexture();
		
		void setRenderTargetDWTexture() const;
		void setRenderTargetNull() const;

		void renderPresent() const;
		
		void renderBox(Rectangle rect, Colour) const;
		void renderText(Text* text, int const xPixel, int const yPixel) const;
		void renderTextbox(Rectangle rect, Colour colour, Text* text, const int xOffset, const int yOffset);
		void renderLines(const std::vector<gfx::Line>& lines, int thickness, const uint8_t drawRGBA_[]);
		
		void renderDrawWindow(Rectangle rect, const uint8_t drawRGBA_[], std::vector<Line> lines) const;
		void clearDrawWindow(Rectangle rect, gfx::Colour colour) const;

		void getMouseState(int& xMouse, int& yMouse, bool dummyValues = false, int dummyX=0, int dummyY=0);
		
	private:
		SDL_Renderer* rendererSDL_;
		SDL_Texture* textureDW_;
		
	};
}
