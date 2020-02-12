#include "WIN_pch.h"
#include "WIN_Utils.h"

using namespace win;
using namespace utils;

// Handles mouse states from SDL for rest of code, also allows setting dummy values for xMouse and yMouse for unit testing
void win::utils::getMouseState(int& xMouse, int& yMouse, bool dummyValues, int dummyX, int dummyY)
{
	if (dummyValues) {
		xMouse = dummyX;
		yMouse = dummyY;
	}
	else {
		SDL_GetMouseState(&xMouse, &yMouse);
	}
}


bool win::utils::filterNumerical(const char c)
{
	if ((c >= '0') && (c <= '9')) {
		return true;
	}
	
	return false;
}
