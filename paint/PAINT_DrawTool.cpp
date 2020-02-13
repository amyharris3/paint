#include "PAINT_pch.h"
#include "PAINT_DrawTool.h"
#include "PAINT_Brush.h"
#include "GFX_Coords.h"

using namespace paint;
using namespace win;


DrawTool::DrawTool(const gfx::Colour colour)
	: drawRGBA_{colour.getRed(),colour.getGreen(),colour.getBlue(),colour.getAlpha()}
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
bool DrawTool::toolFunction(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle const refRect, win::SDLRenderer* renderer)
{
	assert(getActiveBrush() && "activeBrush_ is nullptr.");
	const auto thickness = getActiveBrush()->getThickness();
	assert((thickness == 0) || (thickness == 1) || (thickness == 2) && "brush thickness in renderLines is not 0, 1, or 2.");

	const gfx::Coords rel = { mouseCoords.x - refRect.x, mouseCoords.y - refRect.y };
	const gfx::Coords prevRel = { prevMouseCoords.x - refRect.x, prevMouseCoords.y - refRect.y };
	setALine({ rel.x, rel.y, prevRel.x, prevRel.y });
	renderer->renderLines(gfx::RenderTarget::DRAW_WINDOW, getLines(), thickness, drawRGBA_);
	renderer->switchRenderTarget(gfx::RenderTarget::SCREEN);

	return false;
}

bool DrawTool::toolFunctionEnd(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer)
{
	clearLines();
	return false;
}