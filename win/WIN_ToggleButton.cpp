#include "WIN_ToggleButton.h"
#include "WIN_ButtonUtils.h"
#include "WIN_ButtonGroup.h"
#include <cassert>

using namespace win;

ToggleButton::ToggleButton(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, ToggleActionFunction const act)
	: UIelement(rect, name)
	, action(act)
	, renderer_(renderer)
	, rect_(rect)
	, buttonGroup_(nullptr)
	, state_(off)
	, activated_(true)
{
	texture_ = ButtonUtils::loadSprite(renderer_, spritePath);
	spriteClips_ = ButtonUtils::handleSpriteSheet(texture_);
	activeClip_ = &(spriteClips_[1]);
}

ToggleButton::~ToggleButton()
{
	if (texture_) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}

/* override */
void ToggleButton::draw()
{
	SDL_Rect buttonRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	SDL_RenderCopy(renderer_, texture_, activeClip_, &buttonRect);
}

/* override */
void ToggleButton::mouseEnter()
{
	if (activated_){
		if (state_ == on) {
			activeClip_ = &(spriteClips_[2]);
		}
		else if (state_ == off) {
			activeClip_ = &(spriteClips_[0]);
		}
		else {
			assert((state_ == on) | (state_ == off));
		}
	}

}

/* override */
void ToggleButton::mouseExit()
{
	if (activated_)
	{
		if (state_ == on) {
			activeClip_ = &(spriteClips_[2]);
		}
		else if (state_ == off) {
			activeClip_ = &(spriteClips_[1]);
		}
		else {
			assert((state_ == on) | (state_ == off));
		}
	}

}

/* override */
void ToggleButton::mouseButtonDown(MouseButton b)
{
	if (activated_)
	{
		activeClip_ = &(spriteClips_[2]);
	}

}

/* override */
void ToggleButton::mouseButtonUp(MouseButton b)
{
	if (activated_)
	{
		// set the state of click
		if (state_ == on) {
			state_ = off;
		}
		else if (state_ == off) {
			state_ = on;
		}
		else {
			assert((state_ == on) | (state_ == off));
		}

		if (state_ == on) {
			activeClip_ = &(spriteClips_[2]);
			if (buttonGroup_) {
				buttonGroup_->setSelectedChild(this);
				buttonGroup_->turnOffOtherChildren();
			}
		}
		else if (state_ == off) {
			activeClip_ = &(spriteClips_[0]);
		}
		else {
			assert((state_ == on) | (state_ == off));
		}

		if (action) {
			action(this);
		}
	}


}

void ToggleButton::setButtonGroup(std::shared_ptr<ButtonGroup> buttonGroup)
{
	buttonGroup_ = buttonGroup;
}

void ToggleButton::turnOff()
{
	state_ = off;
	activeClip_ = &(spriteClips_[1]);
	if (action) {
		action(this);
	}
}

void ToggleButton::setActivated(const bool activated)
{
	activated_ = activated;
}

