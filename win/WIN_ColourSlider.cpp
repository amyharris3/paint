#include "WIN_pch.h"
#include "WIN_ColourSlider.h"
#include "GFX_Renderer.h"

using namespace win;

ColourSlider::ColourSlider(gfx::Renderer* renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, uint8_t* linkedVariablePrimary, uint8_t* linkedVariableSecondary, const bool primaryActive)
	: Slider(renderer, rect, name, fillColour, outlineColour, 0, 0, 255)
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
	if (getHold()) {
		moveMarker(e.x);
		valueChangedByMovement();
		
		//updateAndRerender();
	}

	return true;
}

bool ColourSlider::mouseButtonUp(MouseButton button)
{	
	if (getHold()) {
		int xMouse;
		int yMouse;

		getRenderer()->getMouseState(xMouse, yMouse);
		moveMarker(xMouse);
		valueChangedByMovement();
	}	
	holdOff();
	return true;
}
