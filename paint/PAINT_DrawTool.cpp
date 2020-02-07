#include "PAINT_pch.h"
#include "PAINT_DrawTool.h"
#include "PAINT_Brush.h"
#include "WIN_Coords.h"

using namespace paint;
using namespace win;


DrawTool::DrawTool(gfx::Renderer* renderer)
	: renderer_(renderer)
{
	// Activate a default brush
	activeBrush_ = std::make_shared<Brush>(0);
}

//TODO move this to renderer and sort out texture there
void DrawTool::toolFunction(win::Coords relCoords, win::Coords prevRelCoords)
{
	lines_.push_back({ relCoords.x, relCoords.y, prevRelCoords.x, prevRelCoords.y });

	renderer_->setRenderTargetDWTexture();
	renderLines();
	renderer_->setRenderTargetNull();
}

void DrawTool::renderLines() const
{
	assert(activeBrush_ && "activeBrush_ is nullptr.");
	const auto thickness = activeBrush_->getThickness();
	assert((thickness == 0) || (thickness == 1) || (thickness == 2) && "brush thickness in renderLines is not 0, 1, or 2.");

	if (renderer_->notDummy()) {
		renderer_->renderLines(lines_, thickness);
	}
}
