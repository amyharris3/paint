#include "PAINT_pch.h"
#include "PAINT_Rectangle.h"
#include "WIN_Coords.h"
#include "GFX_Line.h"


using namespace paint;
using namespace win;
using namespace gfx;


std::vector<gfx::Line> Rectangle::getGeometry(win::Coords const startCoords, win::Coords const currentCoords)
{
	std::vector<gfx::Line> shapeLines;
	shapeLines.push_back({ startCoords.x, startCoords.y, currentCoords.x, startCoords.y });
	shapeLines.push_back({ currentCoords.x, startCoords.y,  currentCoords.x, currentCoords.y });
	shapeLines.push_back({ currentCoords.x, currentCoords.y, startCoords.x, currentCoords.y });
	shapeLines.push_back({ startCoords.x, currentCoords.y, startCoords.x, startCoords.y });
	return shapeLines;
}
