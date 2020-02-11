#include "PAINT_pch.h"
#include "PAINT_ShapeTool.h"
#include "PAINT_Brush.h"
#include "GFX_Rectangle.h"

using namespace paint;

ShapeTool::ShapeTool(gfx::Renderer* renderer)
	: activeShape_(nullptr)
	, renderer_(renderer)
	, drawRGBA_{ 255,255,255,255 }
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
	renderer_->renderLines(lines, getActiveBrush()->getThickness(), drawRGBA_);
}

void ShapeTool::toolFunctionEnd(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle const refRect)
{
	std::vector<gfx::Line> shiftedLines;
	for (auto line : getLines())
	{
		shiftedLines.push_back({ line.x1 - refRect.x, line.y1 - refRect.y, line.x2 - refRect.x, line.y2 - refRect.y });
	}
	renderer_->setRenderTargetDWTexture();
	renderer_->renderLines(shiftedLines, getActiveBrush()->getThickness(), drawRGBA_);
	renderer_->setRenderTargetNull();
}
