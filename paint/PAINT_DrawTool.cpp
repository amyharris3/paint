#include "PAINT_pch.h"
#include "PAINT_DrawTool.h"
#include "PAINT_Brush.h"
#include "WIN_Coords.h"

using namespace paint;
using namespace win;


DrawTool::DrawTool(gfx::Renderer* renderer)
	: renderer_(renderer)
	, drawRGBA_{255,255,255,255}
{
	// Activate a default brush
	activeBrush_ = std::make_shared<Brush>(0);
}

void DrawTool::setToolColour(const uint8_t RGBA[])
{
	for (auto i = 0; i < 4; i++) {
		drawRGBA_[i] = RGBA[i];
	}
}

void DrawTool::toolFunction(win::Coords relCoords, win::Coords prevRelCoords)
{
	lines_.push_back({ relCoords.x, relCoords.y, prevRelCoords.x, prevRelCoords.y });

	drawLines();
	//This ideally should be removed, but removing the following line causes strange behaviour in Paint - leaving alone for now to prioritise other things
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
}
