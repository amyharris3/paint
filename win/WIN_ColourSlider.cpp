#include "WIN_ColourSlider.h"
#include "../paint/PAINT_Utils.h"

using namespace win;

ColourSlider::ColourSlider(SDL_Renderer* renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, uint8_t* linkedVariable)
	: Slider(renderer, rect, name, fillColour, outlineColour, 0, 0, 255)
	, linkedVariable_(linkedVariable)
{
	setForegroundColour(fillColour);
	setBackgroundColour(outlineColour);
	positionFromValue(*linkedVariable_);
	printPos();
}

void ColourSlider::valueChangedByMovement()
{
	*linkedVariable_ = valueFromPosition();
	auto cpick = paint::utils::findToolWindow(this)->getColourPicker();
	cpick->rerenderColourDisplays();
	cpick->updateColourValueBoxes();
	printf("slider changed linked var %s\n", std::to_string(*linkedVariable_).c_str());
}

void ColourSlider::valueChangedExternally()
{
	positionFromValue(*linkedVariable_);
	updateAndRerender();
}

void ColourSlider::mouseMove()
{
	if (getHold()) {
		moveMarker();
		valueChangedByMovement();
		
		updateAndRerender();
	}
}

void ColourSlider::mouseButtonUp(MouseButton button)
{
	printf("MOUSE UP\n");
	
	if (getHold()) {
		int xMouse;
		int yMouse;

		SDL_GetMouseState(&xMouse, &yMouse);
		moveMarker();
		valueChangedByMovement();
		updateAndRerender();
	}
	
	holdOff();
}
