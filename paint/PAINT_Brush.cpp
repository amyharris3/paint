#include "PAINT_Brush.h"


using namespace paint;

Brush::Brush(const int thickness)
	: thickness_(thickness)
{

}

//// Only defined for round brushes of thickness_, more complex shapes undefined
//std::vector<Coords> Brush::brushArea(const Coords pixel) const
//{
//	std::vector<Coords> returnPixels;
//
//	returnPixels.push_back(pixel);
//	
//	for (auto i = 0; i <= int(round(double(thickness_))); ++i) {
//		returnPixels.push_back(Coords{ pixel.x - i, pixel.y - i });
//		returnPixels.push_back(Coords{ pixel.x + i, pixel.y + i });
//	}
//	
//	return returnPixels;
//}

