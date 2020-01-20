#include "GFX_Rectangle.h"

using namespace gfx;

bool Rectangle::ContainsPoint(const int x, const int y) const
{
	return (x >= this->x) && (y >= this->y) && (x < this->x + this->width) && (y < this->y + this->height);
}