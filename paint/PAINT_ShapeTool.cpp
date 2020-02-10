#include "PAINT_pch.h"
#include "PAINT_ShapeTool.h"
#include "PAINT_Brush.h"
#include "GFX_Rectangle.h"

using namespace paint;

ShapeTool::ShapeTool(SDL_Renderer* renderer, SDL_Texture* texture)
	: activeShape_(nullptr)
	, renderer_(renderer)
	, texture_(texture)
{
	activeBrush_ = std::make_shared<Brush>(0);
}

void ShapeTool::setActiveShape(std::shared_ptr<Shape> shape)
{
	activeShape_ = std::move(shape);
}

void ShapeTool::toolFunction(win::Coords mouseCoords, win::Coords prevMouseCoords, win::Coords startCoords, gfx::Rectangle refRect)
{
	clearLines();
	const win::Coords rel = { mouseCoords.x - refRect.x, mouseCoords.y - refRect.y };
	if (rel.x < 0)
	{
		mouseCoords.x = refRect.x;
	}
	if (rel.y < 0)
	{
		mouseCoords.y = refRect.y;
	}
	if (rel.y > refRect.height)
	{
		mouseCoords.y = refRect.y + refRect.height;
	}
	lines_ = activeShape_->shapeGeometry(startCoords, mouseCoords);
	renderLines(renderer_, lines_);
}

void ShapeTool::toolFunctionEnd(win::Coords mouseCoords, win::Coords prevMouseCoords, win::Coords startCoords, gfx::Rectangle refRect)
{
	std::vector<gfx::Line> shiftedLines;
	for (auto line : lines_)
	{
		shiftedLines.push_back({ line.x1 - refRect.x, line.y1 - refRect.y, line.x2 - refRect.x, line.y2 - refRect.y });
	}
	SDL_SetRenderTarget(renderer_, texture_);
	renderLines(renderer_, shiftedLines);
	SDL_SetRenderTarget(renderer_, nullptr);
}
