#include "GFX_pch.h"
#include "GFX_Text.h"
#include "GFX_Colour.h"

using namespace gfx;

Text::Text()
	: textString_("")
	, renderer_(nullptr)
	, textSize_(12)
	, textFont_(nullptr)
	, textTex_(nullptr)
	, textColour_({ 0, 0, 0, 255 })
	, textWidth_(0)
	, textHeight_(0)
{
}

Text::Text(SDL_Renderer* renderer, Colour const textColour, const char* fontName, int const textSize)
	: Text(renderer, textColour, fontName, textSize, "")
{
}

Text::Text(SDL_Renderer* renderer, Colour const textColour, const char* fontName, int const textSize, const char* textString)
	: textString_(textString)
	, renderer_(renderer)
	, textSize_(textSize)
	, textFont_(TTF_OpenFont(fontName, textSize_))
	, textTex_(nullptr)
	, textColour_({ textColour.getRed(), textColour.getGreen(), textColour.getBlue(), textColour.getAlpha() })
	, textWidth_(0)
	, textHeight_(0)
{
	auto const textSurface = TTF_RenderText_Solid(textFont_, textString_.c_str(), textColour_);
	if (textSurface == nullptr) {
		printf("Error: unable to render text -> SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		textTex_ = SDL_CreateTextureFromSurface(renderer_, textSurface);
		if (textTex_ == nullptr) {
			printf("Error: unable to render text -> SDL Error: %s\n", SDL_GetError());
		}
		else {
			textWidth_ = textSurface->w;
			textHeight_ = textSurface->h;
		}
	}
}

void Text::changeString(const char* newString)
{
	textString_ = newString;
}

void Text::loadFont(const char* fontName)
{
	textFont_ = TTF_OpenFont(fontName, 20);
	if (textFont_ == nullptr){
		printf("Error: unable to load font -> SDL_tff Error: %s\n", TTF_GetError());
	}
}

bool Text::renderText(int const xPixel, int const yPixel)
{
	auto const textSurface = TTF_RenderText_Solid(textFont_, textString_.c_str(), textColour_);
	if (textSurface == nullptr) {
		printf("Error: unable to render text -> SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		textTex_ = SDL_CreateTextureFromSurface(renderer_, textSurface);
		if (textTex_ == nullptr) {
			printf("Error: unable to render text -> SDL Error: %s\n", SDL_GetError());
		}
		else {
			textWidth_ = textSurface->w;
			textHeight_ = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	SDL_Rect textBoxRect = { xPixel, yPixel, textWidth_, textHeight_ };

	SDL_RenderCopy(renderer_, textTex_, nullptr, &textBoxRect);

	return (textTex_ != nullptr);
}