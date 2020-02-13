#include "WIN_pch.h"
#include "WIN_Button.h"
#include "WIN_SDLUtils.h"
#include "WIN_SDLRenderer.h"

using namespace win;

Button::Button(win::SDLRenderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, const ActionFunction act)
	: UIelement(rect, name)
	, action(act)
	, renderer_(renderer)
	, texture_ (SDLUtils::loadSprite(renderer->getSDLRenderer(), spritePath))
	, rect_(rect)
	, mouseDown_(false)
	, mouseDragged_(false)
	, activated_(true)
	, currentClip_(nullptr)
{	
	rect_ = rect;
	texture_ = SDLUtils::loadSprite(renderer_->getSDLRenderer(), spritePath);
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
void Button::draw(SDLRenderer* renderer)
{
	SDL_Rect buttonRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	SDL_RenderCopy(renderer->getSDLRenderer(), texture_, activeClip_, &buttonRect);
}

/* override */
bool Button::mouseEnter(MouseButton button, const bool clicked)
{
	if (activated_) {
		//to handle mouse being dragged in from outside with button held
		if (clicked) {
			mouseDragged_ = true;
		}
		activeClip_ = &(spriteClips_[0]);
	}
	else {
		activeClip_ = &(spriteClips_[3]);
	}
	return true;
}

/* override */
bool Button::mouseExit(MouseButton button, bool clicked)
{
	if (activated_) {
		activeClip_ = &(spriteClips_[1]);
		mouseDragged_ = false;
	}
	else {
		activeClip_ = &(spriteClips_[3]);
	}
	return true;
}

bool Button::mouseMove(SDL_MouseMotionEvent& e)
{
	return false;
}

/* override */
bool Button::mouseButtonDown(MouseButton button, bool clicked)
{
	if (activated_) {
		mouseDown_ = true;
		activeClip_ = &(spriteClips_[2]);
	}
	else {
		activeClip_ = &(spriteClips_[3]);
	}
	return true;
}

/* override */
bool Button::mouseButtonUp(MouseButton button, bool clicked, win::SDLRenderer* renderer)
{
	if (activated_) {
		if (mouseDown_ && !mouseDragged_) {
			activeClip_ = &(spriteClips_[0]);

			if (action) {
				action(this);
			}
		}
		mouseDown_ = false;
		mouseDragged_ = false;
	}
	else {
		activeClip_ = &(spriteClips_[3]);
	}
	return true;
}


void Button::setActivated(const bool activated)
{
	activated_ = activated;
	if (!activated) {
		currentClip_ = activeClip_;
		activeClip_ = &(spriteClips_[3]);
	}
	if (activated == true) {
		activeClip_ = currentClip_;
	}

}
