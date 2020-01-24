#include "GFX_Rectangle.h"

using namespace gfx;

bool Rectangle::ContainsPoint(const int px, const int py) const
{
	return (px >= x) && (py >= y) && (px < x + width) && (py < y + height);
}
