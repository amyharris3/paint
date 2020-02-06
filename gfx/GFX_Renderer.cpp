#include "GFX_Renderer.h"
#include <cassert>
#include "GFX_Rectangle.h"
#include "GFX_Colour.h"
#include "GFX_Text.h"
#include "GFX_Line.h"

using namespace gfx;

//Only use default constructor for debug and unit testing without actually rendering
Renderer::Renderer()
	: rendererSDL_(nullptr)
	, textureDW_(nullptr)
{
}

Renderer::Renderer(SDL_Renderer* renderer)
	: rendererSDL_(renderer)
	, textureDW_(nullptr)
{
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(rendererSDL_);
	rendererSDL_ = nullptr;
}

void Renderer::createDrawWindowTexture(gfx::Rectangle rect)
{
	assert(rendererSDL_);
	textureDW_ = SDL_CreateTexture(rendererSDL_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height);
}

void Renderer::destroyDrawWindowTexture()
{
	assert(rendererSDL_);
	if (textureDW_) {
		SDL_DestroyTexture(textureDW_);
		textureDW_ = nullptr;
	}
}

void Renderer::renderPresent() const
{
	assert(rendererSDL_);
	SDL_RenderPresent(rendererSDL_);
}

void Renderer::renderBox(gfx::Rectangle rect, gfx::Colour colour) const
{
	assert(rendererSDL_);
	SDL_Rect sdlRect{ rect.x, rect.y, rect.width, rect.height };
	SDL_RenderDrawRect(rendererSDL_, &sdlRect);
	uint8_t colourArr[4];
	colour.getComponents(colourArr);
	SDL_SetRenderDrawColor(rendererSDL_, colourArr[0], colourArr[1], colourArr[2], colourArr[3]);
	SDL_RenderFillRect(rendererSDL_, &sdlRect);
}

void Renderer::renderTextbox(gfx::Rectangle rect, gfx::Colour colour, gfx::Text* text, const int xOffset, const int yOffset)
{
	assert(rendererSDL_);
	SDL_Rect outlineRect = { rect.x - 2, rect.y - 2, rect.width + 4, rect.height + 4 };
	SDL_SetRenderDrawColor(rendererSDL_, 0, 0, 0, 255);
	SDL_RenderFillRect(rendererSDL_, &outlineRect);

	SDL_Rect boxRect = { rect.x, rect.y, rect.width, rect.height };
	uint8_t rgba[4];
	colour.getComponents(rgba);
	SDL_SetRenderDrawColor(rendererSDL_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(rendererSDL_, &boxRect);

	//text->render(this, rect.x + xOffset, rect.y + yOffset);
	renderText(text, rect.x + xOffset, rect.y + yOffset);
}

void Renderer::renderText(gfx::Text * text, int const xPixel, int const yPixel) const
{
	assert(rendererSDL_);
	SDL_Texture* textTex_ = nullptr;
	int textHeight = 0;
	int textWidth = 0;
	const SDL_Color textColour{ text->getColour().getRed(), text->getColour().getGreen(), text->getColour().getBlue(), text->getColour().getAlpha() };
	SDL_Surface* textSurface = TTF_RenderText_Solid(text->getFont(), text->getString().c_str(), textColour);
	if (textSurface == nullptr) {
		printf("Error: unable to render text -> SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		textTex_ = SDL_CreateTextureFromSurface(rendererSDL_, textSurface);
		if (textTex_ == nullptr) {
			printf("Error: unable to render text -> SDL Error: %s\n", SDL_GetError());
		}
		else {
			textWidth = textSurface->w;
			textHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	SDL_Rect textboxRect = { xPixel, yPixel, textWidth, textHeight };

	SDL_RenderCopy(rendererSDL_, textTex_, nullptr, &textboxRect);

	assert(textTex_);
}

void Renderer::renderDrawWindow(gfx::Rectangle rect, const uint8_t drawRGBA_[], std::vector<Line> lines) const
{
	assert(rendererSDL_);
	SDL_Rect destRect = { rect.x, rect.y, rect.width, rect.height };
	SDL_RenderCopy(rendererSDL_, textureDW_, nullptr, &destRect);

	SDL_SetRenderDrawColor(rendererSDL_, int(drawRGBA_[0]), int(drawRGBA_[1]), int(drawRGBA_[2]), int(drawRGBA_[3]));
	//for (std::vector<Line>::const_iterator i = lines_.begin(); i != lines_.end(); ++i) {
	for (auto line : lines) {
		SDL_RenderDrawLine(rendererSDL_, line.x1, line.y1, line.x2, line.y2);
	}
	//}
}

void Renderer::clearDrawWindow(gfx::Rectangle rect) const
{
	assert(rendererSDL_);
	SDL_Rect destRect = { rect.x, rect.y, rect.width, rect.height };
	SDL_RenderCopy(rendererSDL_, textureDW_, nullptr, &destRect);
}

// Handles mouse states from SDL for rest of code, also allows setting dummy values for xMouse and yMouse for unit testing
void Renderer::getMouseState(int& xMouse, int& yMouse, bool dummyValues, int dummyX, int dummyY)
{
	if (dummyValues){
		xMouse = dummyX;
		yMouse = dummyY;
	}
	else{
		SDL_GetMouseState(&xMouse, &yMouse);
	}
}