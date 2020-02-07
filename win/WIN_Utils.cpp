#include "WIN_pch.h"
#include "WIN_Utils.h"
#include "GFX_Rectangle.h"

using namespace win;
using namespace utils;

bool win::utils::filterNumerical(const char c)
{
	if ((c >= '0' && c <= '9')) {
		return true;
	}
	
	return false;
}

//TODO: will need to test extensively, to check border cases
// Outcode for draw window clipping
// note we are flipping 'above' and 'below' the rectangle, due to how coordinates work
/*	INSIDE		0000 -> 0
 *	LEFT		0001 -> 1
 *	RIGHT		0010 -> 2
 *	BELOW		0100 -> 4
 *	ABOVE		1000 -> 8
 *	
 *	ABOVE-LEFT	1001 -> 9
 *	BELOW-LEFT	0101 -> 5
 *	ABOVE-RIGHT	1010 -> 10
 *	BELOW-RIGHT	0110 -> 6
 */
int win::utils::findOutcode(const gfx::Rectangle rect, const int x, const int y)
{
	//Initialise outcode as inside the rectangle
	int outcode = 0;

	if (x < rect.x) {
		outcode |= 1;
	}
	else if (x > rect.x + rect.width) {
		outcode |= 2;
	}

	if (y < rect.y) {
		outcode |= 8;
	}
	else if (y > rect.y + rect.height) {
		outcode |= 4;
	}

	return outcode;
}