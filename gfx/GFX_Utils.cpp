#include "GFX_pch.h"
#include "GFX_Utils.h"
#include "GFX_Rectangle.h"
#include <vector>
#include "GFX_Coords.h"


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
int gfx::utils::findOutcode(const Rectangle rect, const int x, const int y)
{
	//Initialise outcode as inside the rectangle
	auto outcode = 0;

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

//using Cohen-Sutherland clipping algorithm
std::vector<gfx::Coords> gfx::utils::clippingHandler(const Rectangle rect, Coords pStart, Coords pEnd)
{
	auto startOutcode = utils::findOutcode(rect, pStart.x, pStart.y);
	auto endOutcode = utils::findOutcode(rect, pEnd.x, pEnd.y);

	while (true) {
		// case where start and end points are within rectangle
		// OR both points share one zone designation outside the rect, so no crossing over into the rect
		if (!(startOutcode | endOutcode) || (startOutcode & endOutcode)) {
			break;
		}
		// one or more point is outside rect and not sharing 'outside zone'
		else {
			// if startOutcode is 0, ie false, then is inside rect, so examine pEnd instead
			const auto examineOutcode = startOutcode ? startOutcode : endOutcode;
			auto x = startOutcode ? pStart.x : pEnd.x;
			auto y = startOutcode ? pStart.y : pEnd.y;

			// find point of intersection with rect
			// using slope formula: y = mx + y0, m = (y-y0)/(x-x0)

			// point is above rect
			if (examineOutcode & 8) {
				x = pStart.x + (pEnd.x - pStart.x) * (rect.y - pStart.y) / (pEnd.y - pStart.y);
				y = rect.y;
			}
			// point is below rect
			else if (examineOutcode & 4) {
				x = pStart.x + (pEnd.x - pStart.x) * (rect.y + rect.height - pStart.y) / (pEnd.y - pStart.y);
				y = rect.y + rect.height;
			}
			// point is left of window
			else if (examineOutcode & 1) {
				x = rect.x;
				y = pStart.y + (pEnd.y - pStart.y) * (rect.x - pStart.x) / (pEnd.x - pStart.x);
			}
			// point is right of rect
			else if (examineOutcode & 2) {
				x = rect.x + rect.width;
				y = pStart.y + (pEnd.y - pStart.y) * (rect.x + rect.width - pStart.x) / (pEnd.x - pStart.x);
			}

			// move the point under examination to the intersection point, then repeat
			if (examineOutcode == startOutcode) {
				pStart.x = x;
				pStart.y = y;
				startOutcode = gfx::utils::findOutcode(rect, pStart.x, pStart.y);
			}
			else {
				pEnd.x = x;
				pEnd.y = y;
				endOutcode = gfx::utils::findOutcode(rect, pEnd.x, pEnd.y);
			}
		}
	}

	std::vector<Coords> returnCoords;
	returnCoords.push_back(pStart);
	returnCoords.push_back(pEnd);

	return returnCoords;
}
