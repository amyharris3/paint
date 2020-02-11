#include "PAINT_pch.h"
#include "PAINT_Triangle.h"
#include "WIN_Coords.h"
#include "GFX_Line.h"

using namespace paint;
using namespace win;

std::vector<gfx::Line> Triangle::getGeometry(win::Coords startCoords, win::Coords currentCoords)
{
	if (startCoords.x > currentCoords.x) {
		auto const tmp = currentCoords.x;
		currentCoords.x = startCoords.x;
		startCoords.x = tmp;
	}
	if (startCoords.y > currentCoords.y) {
		auto const tmp = currentCoords.y;
		currentCoords.y = startCoords.y;
		startCoords.y = tmp;
	}

	std::vector<gfx::Line> shapeLines;
	shapeLines.push_back({ startCoords.x + abs(startCoords.x - currentCoords.x)/2, startCoords.y,  currentCoords.x, currentCoords.y });
	shapeLines.push_back({ currentCoords.x, currentCoords.y, startCoords.x, currentCoords.y });
	shapeLines.push_back({ startCoords.x, currentCoords.y, startCoords.x + abs(startCoords.x - currentCoords.x) / 2, startCoords.y });
	return shapeLines;
}
