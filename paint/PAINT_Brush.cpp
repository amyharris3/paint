#include "PAINT_Brush.h"
#include <cassert>

using namespace paint;

Brush::Brush(const int thickness)
	: thickness_(thickness)
{

}

void Brush::setThickness(const int thickness)
{
	assert((thickness == 0) | (thickness == 1) | (thickness == 2));
	thickness_ = thickness;
}
