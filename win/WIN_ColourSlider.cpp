#include "WIN_ColourSlider.h"

using namespace win;

ColourSlider::ColourSlider(SDL_Renderer* renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, uint8_t* linkedVariablePrimary, uint8_t* linkedVariableSecondary, const bool primaryActive)
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
		*linkedVariablePrimary_ = valueFromPosition();
	}
	else
	{
		*linkedVariableSecondary_ = valueFromPosition();
	}
}

void ColourSlider::valueChangedExternally()
{
	if (primaryActive_) {
		positionFromValue(*linkedVariablePrimary_);
	}
	else
	{
		positionFromValue(*linkedVariableSecondary_);
	}
	//updateAndRerender();
}

bool ColourSlider::mouseMove()
{
	if (getHold()) {
		moveMarker();
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

		SDL_GetMouseState(&xMouse, &yMouse);
		moveMarker();
		valueChangedByMovement();
		//updateAndRerender();
	}	
	holdOff();
	return true;
}
