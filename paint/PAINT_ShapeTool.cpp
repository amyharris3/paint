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
	setActiveBrush(std::make_shared<Brush>(0));
}

void ShapeTool::setActiveShape(std::shared_ptr<Shape> shape)
{
	activeShape_ = std::move(shape);
}

void ShapeTool::toolFunction(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle const refRect)
{
	clearLines();
	const win::Coords rel = { mouseCoords.x - refRect.x, mouseCoords.y - refRect.y };
	if (rel.x < 0) {
		mouseCoords.x = refRect.x;
	}
	if (rel.y < 0) {
		mouseCoords.y = refRect.y;
	}
	if (rel.y > refRect.height) {
		mouseCoords.y = refRect.y + refRect.height;
	}
	auto const lines = activeShape_->getGeometry(startCoords, mouseCoords);
	setLines(lines);
	renderLines(renderer_, lines);
}

void ShapeTool::toolFunctionEnd(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle const refRect)
{
	std::vector<gfx::Line> shiftedLines;
	for (auto line : getLines())
	{
		shiftedLines.push_back({ line.x1 - refRect.x, line.y1 - refRect.y, line.x2 - refRect.x, line.y2 - refRect.y });
	}
	SDL_SetRenderTarget(renderer_, texture_);
	renderLines(renderer_, shiftedLines);
	SDL_SetRenderTarget(renderer_, nullptr);
}
