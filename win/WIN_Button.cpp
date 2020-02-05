#include "WIN_pch.h"
#include "WIN_Button.h"
#include "WIN_SDLUtils.h"

using namespace win;

Button::Button(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, const ActionFunction act)
	: UIelement(rect, name)
	, action(act)
	, buttonState_(ButtonState::BUTTON_SPRITE_MOUSE_OUT)
	, renderer_(renderer->getRendererSDL())
	, texture_ (SDLUtils::loadSprite(renderer, spritePath))
	, rect_(rect)
{
	renderer_ = renderer;
	rect_ = rect;
	texture_ = SDLUtils::loadSprite(renderer_, spritePath);
	spriteClips_ = SDLUtils::handleSpriteSheet(texture_);
	activeClip_ = &(spriteClips_[1]);
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
bool Button::mouseEnter()
{
	activeClip_ = &(spriteClips_[0]);
	return true;
}

/* override */
bool Button::mouseExit()
{
	activeClip_ = &(spriteClips_[1]);
	return true;
}

/* override */
bool Button::mouseButtonDown(MouseButton b)
{
	activeClip_ = &(spriteClips_[2]);
	return true;
}

/* override */
bool Button::mouseButtonUp(MouseButton b)
{
	activeClip_ = &(spriteClips_[0]);

	if (action) {
		action(this);
	}
	return true;
}

