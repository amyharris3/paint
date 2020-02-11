#include "WIN_pch.h"
#include "WIN_ToggleButton.h"
#include "WIN_SDLUtils.h"
#include "WIN_ButtonGroup.h"
#include "WIN_ButtonStates.h"
#include "GFX_Renderer.h"

using namespace win;

ToggleButton::ToggleButton(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, ActionFunction const act)
	: UIelement(rect, name)
	, action(act)
	, renderer_(renderer->getRendererSDL())
	, rect_(rect)
	, buttonGroup_(nullptr)
	, state_(ButtonStates::off)
	, activated_(true)
	, mouseDown_(false)
	, mouseDragged_(false)
{
	texture_ = SDLUtils::loadSprite(renderer_, spritePath);
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
void ToggleButton::draw()
{
	SDL_Rect buttonRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	SDL_RenderCopy(renderer_, texture_, activeClip_, &buttonRect);
}

/* override */
bool ToggleButton::mouseEnter(bool clicked)
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

	return false;
}

/* override */
bool ToggleButton::mouseExit(bool clicked)
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
	mouseDragged_ = false;

	return false;
}

bool ToggleButton::mouseMove(SDL_MouseMotionEvent& e)
{
	return false;
}

/* override */
bool ToggleButton::mouseButtonDown(MouseButton b)
{
	mouseDown_ = true;
	if (activated_) {
		activeClip_ = &(spriteClips_[2]);
	}

	return false;
}

/* override */
bool ToggleButton::mouseButtonUp(MouseButton b)
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
	mouseDragged_ = false;
	return false;
}

void ToggleButton::setButtonGroup(std::shared_ptr<ButtonGroup> buttonGroup)
{
	buttonGroup_ = std::move(buttonGroup);
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
}

