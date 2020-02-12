#include "PAINT_pch.h"
#include "PAINT_Rectangle.h"
#include "GFX_Line.h"
#include "GFX_Coords.h"

using namespace paint;
using namespace gfx;


std::vector<gfx::Line> Rectangle::getGeometry(gfx::Coords const startCoords, gfx::Coords const currentCoords)
{
	std::vector<gfx::Line> shapeLines;
	shapeLines.push_back({ startCoords.x, startCoords.y, currentCoords.x, startCoords.y });
	shapeLines.push_back({ currentCoords.x, startCoords.y,  currentCoords.x, currentCoords.y });
	shapeLines.push_back({ currentCoords.x, currentCoords.y, startCoords.x, currentCoords.y });
	shapeLines.push_back({ startCoords.x, currentCoords.y, startCoords.x, startCoords.y });
	return shapeLines;
}
