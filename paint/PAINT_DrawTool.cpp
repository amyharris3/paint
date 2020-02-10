#include "PAINT_pch.h"
#include "PAINT_DrawTool.h"
#include "PAINT_Brush.h"
#include "WIN_Coords.h"
#include "PAINT_Utils.h"

using namespace paint;
using namespace win;


DrawTool::DrawTool(SDL_Renderer* renderer, SDL_Texture* texture)
	: renderer_(renderer)
	, texture_(texture)
{
	// Activate a default brush
	activeBrush_ = std::make_shared<Brush>(0);
}

void DrawTool::toolFunction(win::Coords mouseCoords, win::Coords prevMouseCoords, win::Coords startCoords, gfx::Rectangle refRect)
{
	const Coords rel = { mouseCoords.x - refRect.x, mouseCoords.y - refRect.y };
	const Coords prevRel = { prevMouseCoords.x - refRect.x, prevMouseCoords.y - refRect.y };
	lines_.push_back({ rel .x, rel.y, prevRel.x, prevRel.y });
	SDL_SetRenderTarget(renderer_, texture_);
	renderLines(renderer_, lines_);
	SDL_SetRenderTarget(renderer_, nullptr);
}

void DrawTool::toolFunctionEnd(win::Coords mouseCoords, win::Coords prevMouseCoords, win::Coords startCoords, gfx::Rectangle refRect)
{
	clearLines();
}
