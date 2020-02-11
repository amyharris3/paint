#include "GFX_pch.h"
#include "GFX_Text.h"
#include "GFX_Colour.h"
#include "GFX_Renderer.h"

using namespace gfx;

//Text::Text()
//	: textString_("")
//	, textSize_(12)
//	, textFont_(nullptr)
//	//, textTex_(nullptr)
//	, textColour_({ 0, 0, 0, 255 })
//	, textWidth_(0)
//	, textHeight_(0)
//{
//}

Text::Text(Colour textColour, const char* fontName, int const textSize)
	: Text(textColour, fontName, textSize, "")
{
}

Text::Text(Colour textColour, const char* fontName, int const textSize, const char* textString)
	: textString_(textString)
	, textSize_(textSize)
	, fontName_(fontName)
	, textFont_(TTF_OpenFont(fontName_, textSize_))
	//, textTex_(nullptr)
	, textColour_( textColour )
	, textWidth_(0)
	, textHeight_(0)
{
	TTF_SizeText(textFont_, textString_.c_str(), &textWidth_, &textHeight_);
}

void Text::changeString(const char* newString)
{
	textString_ = newString;
	TTF_SizeText(textFont_, textString_.c_str(), &textWidth_, &textHeight_);
}

void Text::loadFont(const char* fontName)
{
	fontName_ = fontName;
	textFont_ = TTF_OpenFont(fontName_, textSize_);
	if (textFont_ == nullptr){
		printf("Error: unable to load font -> SDL_tff Error: %s\n", TTF_GetError());
	}
}

void Text::render(Renderer* renderer, int const xPixel, int const yPixel)
{	
	renderer->renderText(RenderTarget::SCREEN, this, xPixel, yPixel);
}