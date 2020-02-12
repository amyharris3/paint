#include "PAINT_pch.h"
#include "PAINT_DrawTool.h"
#include "PAINT_Brush.h"
#include "GFX_Coords.h"

using namespace paint;
using namespace win;


DrawTool::DrawTool(win::SDLRenderer* renderer)
	: renderer_(renderer)
	, drawRGBA_{255,255,255,255}
{
	// Activate a default brush
	setActiveBrush(std::make_shared<Brush>(0));
}

void DrawTool::setToolColour(const uint8_t RGBA[])
{
	for (auto i = 0; i < 4; i++) {
		drawRGBA_[i] = RGBA[i];
	}
}

void DrawTool::toolFunction(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle const refRect)
{
	const Coords rel = { mouseCoords.x - refRect.x, mouseCoords.y - refRect.y };
	const Coords prevRel = { prevMouseCoords.x - refRect.x, prevMouseCoords.y - refRect.y };
	setALine({ rel.x, rel.y, prevRel.x, prevRel.y });
	drawLines();
	renderer_->switchRenderTarget(gfx::RenderTarget::SCREEN);
}

void DrawTool::drawLines() const
{
	assert(activeBrush_ && "activeBrush_ is nullptr.");
	const auto thickness = activeBrush_->getThickness();
	assert((thickness == 0) || (thickness == 1) || (thickness == 2) && "brush thickness in renderLines is not 0, 1, or 2.");

	if (renderer_->notDummy()) {
		renderer_->renderLines(gfx::RenderTarget::DRAWWINDOW, lines_, thickness, drawRGBA_);
	}
void DrawTool::toolFunctionEnd(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect)
{
	clearLines();
}