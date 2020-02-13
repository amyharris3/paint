#include "PAINT_pch.h"
#include "PAINT_DrawWindow.h"
#include "WIN_Mouse.h"
#include "PAINT_DrawTool.h"
#include "WIN_ToggleButton.h"
#include "GFX_Coords.h"
#include "WIN_ButtonStates.h"
#include "PAINT_ShapeTool.h"
#include "PAINT_Utils.h"
#include "GFX_Utils.h"

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(win::SDLRenderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(rect, name)
	, renderer_(renderer)
	, renderTempTexture_(false)
	, activeTool_(nullptr)
	, drawTool_(std::make_shared<DrawTool>(gfx::Colour(255,255,255,255)))
	, shapeTool_(std::make_shared<ShapeTool>(gfx::Colour(255, 255, 255, 255)))
	, primaryColour_(gfx::Colour(255, 255, 255,255))
	, secondaryColour_(gfx::Colour(255, 255, 255, 255))
	, mouseCoords_({ 0,0 })
	, prevMouseCoords_({ 0,0 })
	, startCoord_({0,0})
	, primaryActive_(true)
	, primaryRGBA_{}
	, secondaryRGBA_{}
{
	renderer->createDrawWindowTexture(rect);
	primaryColour_.getComponents(primaryRGBA_);
	secondaryColour_.getComponents(secondaryRGBA_);
}

//DrawWindow::~DrawWindow()
//{
//	//renderer->destroyDrawWindowTexture();
//}

//static void handleMouseUp(MouseButton const b, Tool* tool, gfx::Coords& mouse, gfx::Coords& prevMouse, gfx::Coords& start, gfx::Rectangle const& rect)
//{
//	if (b == MouseButton::Left && tool) {
//		tool->toolFunctionEnd(mouse, prevMouse, start, rect);
//	}
//}

/*override*/

//not really getting many clipping problems with entry into draw window, but adding this as a precaution
bool DrawWindow::mouseEnter(MouseButton button, const bool clicked)
{
	if (clicked) {
		const int xMouse = mouseCoords_.x;
		const int yMouse = mouseCoords_.y;
		auto absCoords = gfx::utils::clippingHandler(getRect(), prevMouseCoords_, { xMouse, yMouse });

		prevMouseCoords_ = { absCoords[0].x, absCoords[0].y };
		mouseCoords_ = { absCoords[1].x, absCoords[1].y };

		mouseButtonDown(button);
		return true;
	}
	return false;
}

//if exit, mouse may move too fast for render lines to keep up, so must interpolate intersect with DW boundary
bool DrawWindow::mouseExit(MouseButton button, bool clicked)
{
	if (clicked) {
		const int xMouse = mouseCoords_.x;
		const int yMouse = mouseCoords_.y;
		auto absCoords = gfx::utils::clippingHandler(getRect(), prevMouseCoords_, { xMouse, yMouse });

		prevMouseCoords_ = { absCoords[0].x, absCoords[0].y };
		mouseCoords_ = { absCoords[1].x, absCoords[1].y };

		mouseButtonDown(button);

		activeTool_->clearLines();

		return true;
	}

	return false;
}

/*override*/
bool DrawWindow::mouseButtonDown(const MouseButton button, bool clicked)
{
	if (button == MouseButton::Left) {
		if (activeTool_) {
			activeTool_->toolFunction(mouseCoords_, prevMouseCoords_, startCoord_, this->getRect(), renderer_);
		}
	}

	return false;
}

/*override*/
bool DrawWindow::mouseButtonUp(MouseButton button, bool clicked, SDLRenderer* renderer)
{
	if (button == MouseButton::Left) {
		if (activeTool_) {
			activeTool_->toolFunctionEnd(mouseCoords_, prevMouseCoords_, startCoord_, this->getRect(), renderer_);
		}
	}

	return false;
}


void DrawWindow::setActiveTool(std::shared_ptr<Tool> tool)
{
	activeTool_ = std::move(tool);
}

void DrawWindow::toggleDrawTool(ToggleButton* b)
{
	if (b->getState() == ButtonStates::on) {
		activeTool_ = drawTool_;
	}
	else if (b->getState() == ButtonStates::off) {
		activeTool_ = nullptr;
	}
}

void DrawWindow::toggleShapeTool(ToggleButton* b)
{
	if (b->getState() == ButtonStates::on) {
		activeTool_ = shapeTool_;
	}
	else if (b->getState() == ButtonStates::off) {
		activeTool_ = nullptr;
	}
}

void DrawWindow::setMouseCoords(const gfx::Coords relCoords)
{
	mouseCoords_ = relCoords;
}

void DrawWindow::setPrevCoords(const gfx::Coords relPrevCoords)
{
	prevMouseCoords_ = relPrevCoords;
}

void DrawWindow::setCanvasColour(const gfx::Colour colour)
{
	setBackgroundColour(colour);
}

void DrawWindow::setPrimaryColour(const gfx::Colour colour)
{
	primaryColour_ = colour;
	primaryColour_.getComponents(primaryRGBA_);
}

void DrawWindow::setSecondaryColour(const gfx::Colour colour)
{
	secondaryColour_ = colour;
	secondaryColour_.getComponents(secondaryRGBA_);
}


void DrawWindow::updateAllToolsRGBA()
{
	uint8_t drawRGBA_[4];
	if (primaryActive_) {
		for (auto i = 0; i < 4; i++) {
			drawRGBA_[i] = primaryRGBA_[i];
		}
	}
	else {
		for (auto i = 0; i < 4; i++) {
			drawRGBA_[i] = secondaryRGBA_[i];
		}
	}
	drawTool_->setToolColour(drawRGBA_);
	shapeTool_->setToolColour(drawRGBA_);
	
}

void DrawWindow::setAllToolsThickness(int const thickness) const
{
	drawTool_->setToolThickness(thickness);
	shapeTool_->setToolThickness(thickness);
}

/*override*/
void DrawWindow::draw(win::SDLRenderer* renderer)
{
	renderer->renderDrawWindowTexture(getRect(), getBackgroundColour(), renderTempTexture_);
}

void DrawWindow::updateAndRerender(win::SDLRenderer* renderer)
{
	draw(renderer);
	renderer->renderPresentScreen();
}

// TODO Needs more work, to properly clear drawWindow
void DrawWindow::clearWindow() const
{
	renderer_->clearDrawWindow(getRect(), getBackgroundColour());
}

void DrawWindow::setStartCoord(gfx::Coords const startCoords)
{
	startCoord_ = startCoords;
}