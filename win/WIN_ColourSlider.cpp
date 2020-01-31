#include "WIN_ColourSlider.h"

using namespace win;

ColourSlider::ColourSlider(SDL_Renderer* renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, uint8_t* linkedVariable)
	: Slider(renderer, rect, name, fillColour, outlineColour, 0, 0, 255)
	, linkedVariable_(linkedVariable)
{
	setForegroundColour(fillColour);
	setBackgroundColour(outlineColour);
	positionFromValue(*linkedVariable_);
}

void ColourSlider::valueChangedByMovement()
{
	*linkedVariable_ = valueFromPosition();
}

void ColourSlider::valueChangedExternally()
{
	positionFromValue(*linkedVariable_);
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
