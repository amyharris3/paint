#include "PAINT_Brush.h"


using namespace paint;



Brush::Brush(int thickness)
	: thickness_(thickness)
{

}


std::vector<Coords> Brush::brushArea(Coords pixel)
{
	std::vector<Coords> returnPixels;

	returnPixels.push_back(pixel);
	for (int i = 0; i <= 5; ++i) {
		returnPixels.push_back(Coords{ pixel.x - i, pixel.y - i });
		returnPixels.push_back(Coords{ pixel.x + i, pixel.y + i });
	}
	return returnPixels;
}

