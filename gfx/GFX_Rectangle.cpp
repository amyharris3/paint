#include "GFX_Rectangle.h"

using namespace gfx;

Rectangle::Rectangle()
	: Rectangle(0, 0, 1, 1)
{
}

Rectangle::Rectangle(const int rx, const int ry, const int w, const int h)
	: x(rx)
	, y(ry)
	, width(w)
	, height(h)
{
}

bool Rectangle::containsPoint(const int px, const int py) const
{
	return (px >= x) && (py >= y) && (px < x + width) && (py < y + height);
}
