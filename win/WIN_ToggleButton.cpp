#include "WIN_pch.h"
#include "WIN_ToggleButton.h"
#include "WIN_SDLUtils.h"
#include "WIN_ButtonGroup.h"
#include "WIN_ButtonStates.h"
#include "GFX_Renderer.h"
#include "WIN_SDLRenderer.h"
#include "WIN_DisabledUIelementGroup.h"

using namespace win;

ToggleButton::ToggleButton(win::SDLRenderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, ActionFunction const act)
	: UIelement(rect, name)
	, action(act)
	, renderer_(renderer)
	, rect_(rect)
	, buttonGroup_(nullptr)
	, state_(ButtonStates::off)
	, mouseDown_(false)
	, mouseDragged_(false)
	, activated_(true)
	, currentClip_(nullptr)
{
	texture_ = SDLUtils::loadSprite(renderer_->getSDLRenderer(), spritePath);
	spriteClips_ = SDLUtils::handleSpriteSheet(texture_);
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
void ToggleButton::draw(win::SDLRenderer* renderer)
{
	SDL_Rect buttonRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	SDL_RenderCopy(renderer->getSDLRenderer(), texture_, activeClip_, &buttonRect);
}

/* override */
bool ToggleButton::mouseEnter(MouseButton button, const bool clicked)
{
	if (clicked) {
		mouseDragged_ = true;
	}
	
	if (activated_) {
		if (state_ == ButtonStates::on) {
			activeClip_ = &(spriteClips_[2]);
		}
		else if (state_ == ButtonStates::off) {
			activeClip_ = &(spriteClips_[0]);
		}
		else {
			assert(!"Invalid state");
		}
	}
	else {
		activeClip_ = &(spriteClips_[3]);
	}

	return false;
}

/* override */
bool ToggleButton::mouseExit(MouseButton button, bool clicked)
{
	if (activated_) {
		if (state_ == ButtonStates::on) {
			activeClip_ = &(spriteClips_[2]);
		}
		else if (state_ == ButtonStates::off) {
			activeClip_ = &(spriteClips_[1]);
		}
		else {
			assert(!"Invalid state");
		}
	}
	else {
		activeClip_ = &(spriteClips_[3]);
	}
	
	mouseDragged_ = false;

	return false;
}

bool ToggleButton::mouseMove(SDL_MouseMotionEvent& e)
{
	return false;
}

/* override */
bool ToggleButton::mouseButtonDown(MouseButton button, bool clicked)
{
	mouseDown_ = true;
	if (activated_) {
		activeClip_ = &(spriteClips_[2]);
	}
	else {
		activeClip_ = &(spriteClips_[3]);
	}

	return false;
}

/* override */
bool ToggleButton::mouseButtonUp(MouseButton button, bool clicked, SDLRenderer* renderer)
{
	mouseDown_ = false;
	if (activated_ && !mouseDragged_) {
		// set the state of click
		if (state_ == ButtonStates::on) {
			state_ = ButtonStates::off;
		}
		else if (state_ == ButtonStates::off) {
			state_ = ButtonStates::on;
		}
		else {
			assert(!"Invalid state");
		}

		if (state_ == ButtonStates::on) {
			activeClip_ = &(spriteClips_[2]);
			if (buttonGroup_) {
				buttonGroup_->setSelectedChildAndTurnOffOthers(this);
			}
		}
		else if (state_ == ButtonStates::off) {
			activeClip_ = &(spriteClips_[0]);
		}
		else {
			assert(!"Invalid state");
		}

		if (action) {
			action(this);
		}
	}
	else if (activated_ == false){
		activeClip_ = &(spriteClips_[3]);
	}
	mouseDragged_ = false;
	return false;
}

void ToggleButton::setButtonGroup(std::shared_ptr<ButtonGroup> buttonGroup)
{
	buttonGroup_ = std::move(buttonGroup);
}

void ToggleButton::setDisableGroup(std::shared_ptr<DisabledUIelementGroup> disableGroup)
{
	disableGroup_ = std::move(disableGroup);
}

void ToggleButton::turnOff()
{
	state_ = ButtonStates::off;
	activeClip_ = &(spriteClips_[1]);
	if (action) {
		action(this);
	}
}

void ToggleButton::setActivated(const bool activated)
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

