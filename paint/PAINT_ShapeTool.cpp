#include "PAINT_pch.h"
#include "PAINT_ShapeTool.h"
#include "PAINT_Brush.h"
#include "GFX_Rectangle.h"
#include "WIN_SDLRenderer.h"

using namespace paint;

ShapeTool::ShapeTool(gfx::Colour colour)
	: activeShape_(nullptr)
	, drawRGBA_{ colour.getRed(),colour.getGreen(),colour.getBlue(),colour.getAlpha() }
{
	setActiveBrush(std::make_shared<Brush>(0));
}

void ShapeTool::setToolColour(const uint8_t RGBA[])
{
	for (auto i = 0; i < 4; i++) {
		drawRGBA_[i] = RGBA[i];
	}
}

void ShapeTool::setActiveShape(std::shared_ptr<Shape> shape)
{
	activeShape_ = std::move(shape);
}

bool ShapeTool::toolFunction(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle const refRect, win::SDLRenderer* renderer)
{
	clearLines();
	const gfx::Coords rel = { mouseCoords.x - refRect.x, mouseCoords.y - refRect.y };
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
	renderer->renderLines(gfx::RenderTarget::SCREEN, lines, getActiveBrush()->getThickness(), drawRGBA_);

	return false;
}

bool ShapeTool::toolFunctionEnd(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle const refRect, win::SDLRenderer* renderer)
{
	assert(getActiveBrush() && "activeBrush_ is nullptr.");
	const auto thickness = getActiveBrush()->getThickness();
	assert((thickness == 0) || (thickness == 1) || (thickness == 2) && "brush thickness in renderLines is not 0, 1, or 2.");
	
	std::vector<gfx::Line> shiftedLines;
	for (auto line : getLines())
	{
		shiftedLines.push_back({ line.x1 - refRect.x, line.y1 - refRect.y, line.x2 - refRect.x, line.y2 - refRect.y });
	}
	renderer->renderLines(gfx::RenderTarget::DRAW_WINDOW, shiftedLines, thickness, drawRGBA_);
	renderer->switchRenderTarget(gfx::RenderTarget::SCREEN);

	//clearLines();
	
	return false;
}
