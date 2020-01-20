#include "GFX_Colour.h"

using namespace gfx;

Colour::Colour(int r, int g, int b, int a)
	: r_(r)
	, g_(g)
	, b_(b)
	, a_(a)
{
}

int* Colour::getColour()
{
	int colourArr[4] = { r_, g_, b_, a_ };
	return colourArr;
}

