#pragma once
#include "GFX_Colour.h"
#include "GFX_Rectangle.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

// Handling text loading and rendering
namespace gfx
{
	class Colour;

	class Text
	{
	public:
		//Empty constructor is for test only
		Text(); // = delete;
		Text(SDL_Renderer* renderer, Colour textColour = {0, 0, 0, 255}, const char* fontName = "OpenSans-Regular.ttf", int const textSize = 12);
		Text(SDL_Renderer* renderer, Colour textColour, const char* fontName, int const textSize, const char* textString);
		~Text() = default;
		Text(const Text & that) = default;
		Text(Text && that) = default;
		Text& operator=(const Text & that) = default;
		Text& operator=(Text && that) = default;

		TTF_Font* getFont() const { return textFont_; }
		int getWidth() const { return textWidth_; }
		int getHeight() const { return textHeight_; }

		std::string getString() const { return textString_; }
		void changeString(const char* newString);
		void loadFont(const char* fontName);
		bool renderText(int const xPixel, int const yPixel);
		
	private:

		std::string textString_;

		SDL_Renderer* renderer_;
		TTF_Font* textFont_;
		int textSize_;
		SDL_Texture* textTex_;
		SDL_Color textColour_;
		int textWidth_;
		int textHeight_;
		
	};
}
