#include "WIN_EditTextbox.h"
#include "SDL.h"
#include "SDL_ttf.h"

using namespace win;

EditTextbox::EditTextbox(gfx::Rectangle rect, const char* name, SDL_Renderer* renderer, std::shared_ptr<int> linkedVariable)
	: UIelement(rect, name)
	, renderer_(renderer)
	, textColour_({ 0, 0, 0, 0xFF })
	, linkedVariable_(std::move(linkedVariable))
{
	setBackgroundColour(gfx::Colour(255, 255, 255, 255));
	textFont_ = TTF_OpenFont("Cabin-Regular-TTF.ttf", 20);
	//textTex_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, getRect().width, getRect().height);
	//loadedText_ = std::to_string(*linkedVariable_);
	loadedText_ = "100";
}


bool EditTextbox::renderText()
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(textFont_, loadedText_.c_str(), textColour_);
    if (textSurface == nullptr)
    {
        printf("Error: unable to render text -> SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
		textTex_ = SDL_CreateTextureFromSurface(renderer_, textSurface);
        if (textTex_ == nullptr)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(textSurface);
    }

    //Return success
    return textTex_ != nullptr;
}


void EditTextbox::draw()
{
	SDL_Rect boxRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	uint8_t rgba[4];
	getBackgroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);

	//auto textTex = SDL_CreateTexture(renderer_,	SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, getRect().width, getRect().height);

	
	//textTex.loadFromRenderedText(loadedText_.c_str(), textColour_);


}
