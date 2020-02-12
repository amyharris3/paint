#include "WIN_pch.h"
#include "WIN_ColourSlider.h"
#include "GFX_Renderer.h"
#include "WIN_SDLRenderer.h"
#include "WIN_Utils.h"

using namespace win;

ColourSlider::ColourSlider(gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, uint8_t* linkedVariablePrimary, uint8_t* linkedVariableSecondary, const bool primaryActive)
	: Slider(rect, name, fillColour, outlineColour, 0, 0, 255)
	, linkedVariablePrimary_(linkedVariablePrimary)
	, linkedVariableSecondary_(linkedVariableSecondary)
	, primaryActive_(primaryActive)
{
	setForegroundColour(fillColour);
	setBackgroundColour(outlineColour);
	
	valueChangedExternally();
}

void ColourSlider::valueChangedByMovement() const
{
	if (primaryActive_) {
		*linkedVariablePrimary_ = getApproxValueFromPosition();
	}
	else
	{
		*linkedVariableSecondary_ = getApproxValueFromPosition();
	}
}

void ColourSlider::valueChangedExternally()
{
	if (primaryActive_) {
		setMarkerValue(*linkedVariablePrimary_);
	}
	else
	{
		setMarkerValue(*linkedVariableSecondary_);
	}
	//updateAndRerender();
}

bool ColourSlider::mouseMove(SDL_MouseMotionEvent& e)
{
	if (getHold() && !getClickDownFromOutside()) {
		moveMarker(e.x);
		valueChangedByMovement();
		
		//updateAndRerender();
	}

	return true;
}

bool ColourSlider::mouseButtonUp(MouseButton button, win::SDLRenderer* renderer)
{	
	if (getHold() && !getClickDownFromOutside()) {
		int xMouse;
		int yMouse;

		win::utils::getMouseState(xMouse, yMouse);
		moveMarker(xMouse);
		valueChangedByMovement();
	}	
	holdOff();
	setClickDownFromOutside(false);
	return true;
}
