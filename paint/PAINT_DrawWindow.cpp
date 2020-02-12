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
	, activeTool_(nullptr)
	, drawTool_(std::make_shared<DrawTool>(renderer))
	, primaryColour_(gfx::Colour(255, 255, 255,255))
	, secondaryColour_(gfx::Colour(255, 255, 255, 255))
	, mouseCoords_({ 0,0 })
	, prevMouseCoords_({ 0,0 })
	, startCoord_({0,0})
	, primaryActive_(true)
	, primaryRGBA_{}
	, secondaryRGBA_{}
{
	//texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height);
	renderer->createDrawWindowTexture(rect);
	primaryColour_.getComponents(primaryRGBA_);
	secondaryColour_.getComponents(secondaryRGBA_);
	drawTool_ = std::make_shared<DrawTool>(renderer_);
	shapeTool_ = std::make_shared<ShapeTool>(renderer_);
}

DrawWindow::~DrawWindow()
{
	//renderer->destroyDrawWindowTexture();
}

static void handleMouseUp(MouseButton const b, Tool* tool, Coords& mouse, Coords& prevMouse, Coords& start, gfx::Rectangle const& rect)
{
	if (b == MouseButton::Left && tool) {
		tool->toolFunctionEnd(mouse, prevMouse, start, rect);
	}
}

/*override*/

//not really getting many clipping problems with entry into draw window, but adding this as a precaution
bool DrawWindow::mouseEnter(bool clicked)
{
	const int xMouse = mouseCoords_.x;
	const int yMouse = mouseCoords_.y; 
	auto absCoords = gfx::utils::clippingHandler(getRect(), prevMouseCoords_, { xMouse, yMouse });

	prevMouseCoords_ = { absCoords[0].x, absCoords[0].y };
	mouseCoords_ = { absCoords[1].x, absCoords[1].y };

	if (drawToggle_) {
		mouseButtonDown(MouseButton::Left);
	}

	drawToggle_ = false;

	return false;
}


//if exit, mouse may move too fast for render lines to keep up, so must interpolate intersect with DW boundary
bool DrawWindow::mouseExit(bool clicked)
{
	const int xMouse = mouseCoords_.x;
	const int yMouse = mouseCoords_.y;
	//SDL_GetMouseState(&xMouse, &yMouse);
	auto absCoords = gfx::utils::clippingHandler(getRect(),prevMouseCoords_, { xMouse, yMouse });

	prevMouseCoords_ = { absCoords[0].x, absCoords[0].y };
	mouseCoords_ = { absCoords[1].x, absCoords[1].y };

	if (drawToggle_) {
		mouseButtonDown(MouseButton::Left);
	}

	drawToggle_ = false;

	return false;
}


//if exit, mouse may move too fast for render lines to keep up, so must interpolate intersect with DW boundary
bool DrawWindow::mouseExit(const MouseButton button, bool clicked)
{
	drawToggle_ = true;
	if (b == MouseButton::Left) {
		if (activeTool_) {
			const gfx::Coords prevRel = { prevMouseCoords_.x - this->getRect().x, prevMouseCoords_.y - this->getRect().y };
			const gfx::Coords rel = { mouseCoords_.x - this->getRect().x, mouseCoords_.y - this->getRect().y };

	prevMouseCoords_ = { absCoords[0].x, absCoords[0].y};
	mouseCoords_ = { absCoords[1].x, absCoords[1].y };

	if (drawToggle_) {
	handleMouseUp(button, activeTool_.get(), mouseCoords_, prevMouseCoords_, startCoord_, this->getRect());
	}

	return true;
}

/*override*/
bool DrawWindow::mouseButtonUp(win::MouseButton const b, win::SDLRenderer* renderer)
{
	if (button == MouseButton::Left) {
		if (activeTool_) {
			activeTool_->toolFunction(mouseCoords_, prevMouseCoords_, startCoord_, this->getRect());
		}
	}

	return false;
}



/*override*/
bool DrawWindow::mouseButtonUp(const MouseButton button, bool clicked)
{
	handleMouseUp(button, activeTool_.get(), mouseCoords_, prevMouseCoords_, startCoord_, this->getRect());
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


void DrawWindow::updateDrawToolRGBA()
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

}

/*override*/
void DrawWindow::draw(win::SDLRenderer* renderer)
{
	renderer->renderDrawWindow(getRect(), getBackgroundColour());
}

void DrawWindow::updateAndRerender(win::SDLRenderer* renderer)
{
	draw(renderer);
	renderer->renderPresentScreen();
}

// TODO Needs more work, to properly clear drawWindow
void DrawWindow::clearWindow() const
{
	//renderer_->setRenderTargetDWTexture();
	renderer_->clearDrawWindow(getRect(), getBackgroundColour());
	//renderer_->setRenderTargetNull();
}