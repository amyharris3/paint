#include "WIN_Button.h"
#include <SDL_image.h>


using namespace win;

Button::Button(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name)
	: UIelement(rect, name)
{
	renderer_ = renderer;
	//texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height);
	rect_ = rect;
	texture_ = loadSprite("button_test.png");
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
	SDL_Rect sdlRect = { rect_.x, rect_.y, rect_.width, rect_.height };
	SDL_RenderCopy(renderer_, texture_, NULL, &sdlRect);
}

void Button::mouseEnter()
{
	//buttonState_ = ButtonState::BUTTON_SPRITE_MOUSE_OVER;
}

void Button::mouseExit()
{
	//buttonState_ = ButtonState::BUTTON_SPRITE_MOUSE_OUT;
}

void Button::mouseButtonDown(MouseButton b, int xPixel, int yPixel)
{
	//buttonState_ = ButtonState::BUTTON_SPRITE_MOUSE_DOWN;
}

void Button::mouseButtonUp(MouseButton b)
{
	//buttonState_ = ButtonState::BUTTON_SPRITE_MOUSE_UP;
}


SDL_Texture* Button::loadSprite(const char* path)
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