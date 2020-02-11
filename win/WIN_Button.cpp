#include "WIN_pch.h"
#include "WIN_Button.h"
#include "WIN_SDLUtils.h"

using namespace win;

Button::Button(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, const ActionFunction act)
	: UIelement(rect, name)
	, action(act)
	, renderer_(renderer->getRendererSDL())
	, texture_ (SDLUtils::loadSprite(renderer->getRendererSDL(), spritePath))
	, rect_(rect)
	, mouseDown_(false)
	, mouseDragged_(false)
{
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
bool Button::mouseEnter(MouseButton button, const bool clicked)
{
	//to handle mouse being dragged in from outside with button held
	if (clicked) {
		mouseDragged_ = true;
	}
	activeClip_ = &(spriteClips_[0]);
	return true;
}

/* override */
bool Button::mouseExit(MouseButton button, bool clicked)
{
	activeClip_ = &(spriteClips_[1]);
	return true;
}

bool Button::mouseMove(SDL_MouseMotionEvent& e)
{
	return false;
}

/* override */
bool Button::mouseButtonDown(MouseButton button, bool clicked)
{
	mouseDown_ = true;
	activeClip_ = &(spriteClips_[2]);
	return true;
}

/* override */
bool Button::mouseButtonUp(MouseButton button, bool clicked)
{
	if (mouseDown_ && !mouseDragged_) {
		activeClip_ = &(spriteClips_[0]);

		if (action) {
			action(this);
		}
	}
	mouseDown_ = false;
	mouseDragged_ = false;
	return true;
}
