#include "PAINT_Brush.h"
#include <iostream>
#include <cassert>

using namespace paint;

Brush::Brush(const int thickness)
	: thickness_(thickness)
{
	assert((thickness == 0) || (thickness == 1) || (thickness == 2) && "Brush initialised with thickness other than 0, 1 or 2.");
}

void Brush::setThickness(const int thickness)
{
	try {
		if (!((thickness == 0) || (thickness == 1) || (thickness == 2))) {
			throw std::runtime_error("Brush thickness set to value other than 0, 1 or 2.");
		}
	}
	catch(std::runtime_error &e)
	{
		std::cout << e.what() << '\n';
		throw;
	}
	thickness_ = thickness;
}
