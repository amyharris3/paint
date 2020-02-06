#include "PAINT_pch.h"
#include "PAINT_Brush.h"

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
		// Note: suppresses release build warning.
		if (e.what()) {
#		if defined(_DEBUG)
			std::cout << e.what() << '\n';
#		endif
		}
		throw;
	}
	thickness_ = thickness;
}
