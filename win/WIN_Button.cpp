#include "WIN_Button.h"
#include <SDL_image.h>
#include <cassert>
#include <iostream>


using namespace win;

Button::Button(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, const ActionFunction act)
	: UIelement(rect, name)
	, action(act)
	, buttonState_(ButtonState::BUTTON_SPRITE_MOUSE_OUT)
	, renderer_(renderer->getRendererSDL())
	//texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height)
	, texture_ (loadSprite(spritePath))
	, rect_(rect)
	, spriteClips_()
	, clicked_(false)
{
	handleSpriteSheet();
	activeClip_ = &(spriteClips_[1]);
}

Button::~Button()
{
	if (texture_) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}

void Button::draw()
{
	SDL_Rect buttonRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	SDL_RenderCopy(renderer_, texture_, activeClip_, &buttonRect);
}


bool Button::mouseEnter()
{
	if (clicked_) {
		activeClip_ = &(spriteClips_[2]);
	}
	else {
		activeClip_ = &(spriteClips_[0]);
	}
	buttonState_ = ButtonState::BUTTON_SPRITE_MOUSE_OVER;

	return true;
}

bool Button::mouseExit()
{
	if (clicked_) {
		activeClip_ = &(spriteClips_[2]);
	}
	else {
		activeClip_ = &(spriteClips_[1]);
	}
	buttonState_ = ButtonState::BUTTON_SPRITE_MOUSE_OUT;

	return true;
}

bool Button::mouseButtonDown(MouseButton b)
{

	buttonState_ = ButtonState::BUTTON_SPRITE_MOUSE_DOWN;
	activeClip_ = &(spriteClips_[2]);
	return true;
}

bool Button::mouseButtonUp(MouseButton b)
{
	clicked_ = !clicked_;
	buttonState_ = ButtonState::BUTTON_SPRITE_MOUSE_UP;
	if (clicked_) {
		activeClip_ = &(spriteClips_[2]);
	}
	else {
		activeClip_ = &(spriteClips_[0]);
	}

	// If mouse is still over button at this point...
	if (action) {
		action(this);
	}
	return true;
}


SDL_Texture* Button::loadSprite(const char* path) const
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void Button::handleSpriteSheet()
{
	//Load sprite sheet texture
	assert(texture_);

	//Set top left sprite
	spriteClips_[0].x = 0;
	spriteClips_[0].y = 0;
	spriteClips_[0].w = 100;
	spriteClips_[0].h = 100;

	//Set top right sprite
	spriteClips_[1].x = 100;
	spriteClips_[1].y = 0;
	spriteClips_[1].w = 100;
	spriteClips_[1].h = 100;

	//Set bottom left sprite
	spriteClips_[2].x = 0;
	spriteClips_[2].y = 100;
	spriteClips_[2].w = 100;
	spriteClips_[2].h = 100;

	//Set bottom right sprite
	spriteClips_[3].x = 100;
	spriteClips_[3].y = 100;
	spriteClips_[3].w = 100;
	spriteClips_[3].h = 100;
}