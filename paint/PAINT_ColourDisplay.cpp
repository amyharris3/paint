#include "PAINT_pch.h"
#include "PAINT_ColourDisplay.h"
#include "../paint/PAINT_Utils.h"
#include "WIN_SDLRenderer.h"

using namespace paint;


ColourDisplay::ColourDisplay(const gfx::Rectangle rect, const char* name, uint8_t displayColour[], const bool isActive)
	: UIelement(rect, name)
	, isActive_(isActive)
	, isClicked_(false)
	, mouseDragged_(false)
{
	this->setForegroundColour(gfx::Colour(displayColour[0], displayColour[1], displayColour[2], displayColour[3]));
	if (isActive_)
	{
		this->setBackgroundColour(gfx::Colour(0, 0, 0, 255));
	}
	else
	{
		this->setBackgroundColour(gfx::Colour(200, 200, 200, 200));
	}
}

void ColourDisplay::setColour(const gfx::Colour colour)
{
	setForegroundColour(colour);
}

void ColourDisplay::setOutlineColour(const gfx::Colour outlineColour)
{
	this->setBackgroundColour(outlineColour);
}

void ColourDisplay::setActive()
{
	isActive_ = true;
	setBackgroundColour(gfx::Colour(0, 0, 0, 255));
}

void ColourDisplay::setInactive()
{
	isActive_ = false;
	setBackgroundColour(gfx::Colour(200, 200, 200, 200));
}

void ColourDisplay::swapIsActive()
{
	if (isActive_){
		setInactive();
	}
	else {
		setActive();
	}
}

void ColourDisplay::update()
{
	
}

void ColourDisplay::draw(win::SDLRenderer* renderer)
{
	renderer->renderBox(gfx::RenderTarget::SCREEN, getRect(), getBackgroundColour());
	renderer->renderBox(gfx::RenderTarget::SCREEN, { getRect().x + 5, getRect().y + 5, getRect().width - 10, getRect().height - 10 }, getForegroundColour());
}

bool ColourDisplay::mouseEnter(win::MouseButton button, const bool clicked)
{
	if (clicked) {
		mouseDragged_ = true;
	}
	return false;
}

bool ColourDisplay::mouseExit(win::MouseButton button, bool clicked)
{
	isClicked_ = false;
	mouseDragged_ = false;
	return false;
}

bool ColourDisplay::mouseMove(SDL_MouseMotionEvent& e)
{
	if (isClicked_ && (e.xrel != 2 || e.yrel != 2)) {
		mouseDragged_ = true;
	}

	return false;
}

bool ColourDisplay::mouseButtonDown(win::MouseButton button, bool clicked)
{
	isClicked_ = true;
	return false;
}

bool ColourDisplay::mouseButtonUp(win::MouseButton const button, bool clicked, win::SDLRenderer* renderer)
{
	if (isClicked_ && !mouseDragged_) {
		const auto colourPicker = paint::utils::findToolWindow(this)->getColourPicker();
		colourPicker->swapActiveColour();
	}
	isClicked_ = false;
	mouseDragged_ = false;
	return true;
}