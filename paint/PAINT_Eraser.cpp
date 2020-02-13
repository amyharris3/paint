#include "PAINT_pch.h"
#include "PAINT_Eraser.h"

using namespace paint;

bool Eraser::toolFunction(gfx::Coords& , gfx::Coords&, gfx::Coords&, gfx::Rectangle refRect, win::SDLRenderer* renderer)
{
	// TODO
	return false;
}

bool Eraser::toolFunctionEnd(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer)
{
	return false;
}
