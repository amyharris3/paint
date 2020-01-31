#include "WIN_Button.h"
#include <SDL_image.h>
#include "WIN_ButtonUtils.h"


using namespace win;

Button::Button(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, const ActionFunction act)
	: UIelement(rect, name)
	, action(act)
{
	renderer_ = renderer;
	rect_ = rect;
	texture_ = ButtonUtils::loadSprite(renderer_, spritePath);
	spriteClips_ = ButtonUtils::handleSpriteSheet(texture_);
	activeClip_ = &(spriteClips_[1]);
	clicked_ = false;
}

Button::~Button()
{
	if (texture_) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}

/* override */
void Button::draw()
{
	SDL_Rect buttonRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	SDL_RenderCopy(renderer_, texture_, activeClip_, &buttonRect);
}

/* override */
void Button::mouseEnter()
{
		activeClip_ = &(spriteClips_[0]);
}

/* override */
void Button::mouseExit()
{

	activeClip_ = &(spriteClips_[1]);

}

/* override */
void Button::mouseButtonDown(MouseButton b)
{
	activeClip_ = &(spriteClips_[2]);
}

/* override */
void Button::mouseButtonUp(MouseButton b)
{
	activeClip_ = &(spriteClips_[0]);

	if (action) {
		action(this);
	}
}

