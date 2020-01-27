#include "GFX_Rectangle.h"

using namespace gfx;

bool Rectangle::containsPoint(const int px, const int py) const
{
	return (px >= x) && (py >= y) && (px < x + width) && (py < y + height);
}
