#include "PAINT_pch.h"
#include "PAINT_DrawWindow.h"
#include "WIN_Mouse.h"
#include "PAINT_DrawTool.h"
#include "WIN_ToggleButton.h"
#include "WIN_Coords.h"
#include "WIN_ButtonStates.h"
#include "PAINT_ShapeTool.h"
#include "PAINT_Utils.h"
#include "WIN_Utils.h"

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(gfx::Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window( renderer, rect, name)
	, renderer_(renderer)
	, activeTool_(nullptr)
	, drawTool_(std::make_shared<DrawTool>(renderer_))
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
	renderer_->createDrawWindowTexture(rect);
	primaryColour_.getComponents(primaryRGBA_);
	secondaryColour_.getComponents(secondaryRGBA_);
	drawTool_ = std::make_shared<DrawTool>(renderer_);
	shapeTool_ = std::make_shared<ShapeTool>(renderer_);
}

DrawWindow::~DrawWindow()
{
	renderer_->destroyDrawWindowTexture();
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
	auto absCoords = clippingHandler(prevMouseCoords_, { xMouse, yMouse });

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
	auto absCoords = clippingHandler(prevMouseCoords_, { xMouse, yMouse });

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
	const int xMouse = mouseCoords_.x;
	const int yMouse = mouseCoords_.y;
	//SDL_GetMouseState(&xMouse, &yMouse);
	auto absCoords = clippingHandler(prevMouseCoords_, { xMouse, yMouse });

	prevMouseCoords_ = { absCoords[0].x, absCoords[0].y};
	mouseCoords_ = { absCoords[1].x, absCoords[1].y };

	if (drawToggle_) {
	handleMouseUp(button, activeTool_.get(), mouseCoords_, prevMouseCoords_, startCoord_, this->getRect());
	}

	return true;
}

/*override*/
bool DrawWindow::mouseButtonDown(const MouseButton button, bool clicked)
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

void DrawWindow::setMouseCoords(const win::Coords relCoords)
{
	mouseCoords_ = relCoords;
}

void DrawWindow::setPrevCoords(const win::Coords relPrevCoords)
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
void DrawWindow::draw()
{
	renderer_->renderDrawWindow(getRect(), getBackgroundColour());
}

void DrawWindow::updateAndRerender()
{
	draw();
	renderer_->renderPresentScreen();
}

// TODO Needs more work, to properly clear drawWindow
void DrawWindow::clearWindow() const
{
	//renderer_->setRenderTargetDWTexture();
	renderer_->clearDrawWindow(getRect(), getBackgroundColour());
	//renderer_->setRenderTargetNull();
}

//using Cohen-Sutherland clipping algorithm
std::vector<win::Coords> DrawWindow::clippingHandler(win::Coords pStart, win::Coords pEnd) const
{
	const auto rect = getRect();

	auto startOutcode = win::utils::findOutcode(rect, pStart.x, pStart.y);
	auto endOutcode = win::utils::findOutcode(rect, pEnd.x, pEnd.y);
	
	int startOutcode = win::utils::findOutcode(rect, pStart.x, pStart.y);
	int endOutcode = win::utils::findOutcode(rect, pEnd.x, pEnd.y);

	while(true){
		// case where start and end points are within rectangle
		// OR both points share one zone designation outside the rect, so no crossing over into the rect
		if (!(startOutcode | endOutcode) || (startOutcode & endOutcode)){
			break;
		}
		// one or more point is outside rect and not sharing 'outside zone'
		else {
			// if startOutcode is 0, ie false, then is inside rect, so examine pEnd instead
			const auto examineOutcode = startOutcode ? startOutcode : endOutcode;
			int x = startOutcode ? pStart.x : pEnd.x;
			int y = startOutcode ? pStart.y : pEnd.y;
	
			// find point of intersection with rect
			// using slope formula: y = mx + y0, m = (y-y0)/(x-x0)
			
			// point is above rect
			if (examineOutcode & 8){
				x = pStart.x + (pEnd.x - pStart.x) * (rect.y - pStart.y) / (pEnd.y - pStart.y);
				y = rect.y;
			}
			// point is below rect
			else if (examineOutcode & 4) {
				x = pStart.x + (pEnd.x - pStart.x) * (rect.y + rect.height - pStart.y) / (pEnd.y - pStart.y);
				y = rect.y + rect.height;
			}
			// point is left of window
			else if (examineOutcode & 1) {
				x = rect.x;
				y = pStart.y + (pEnd.y - pStart.y) * (rect.x - pStart.x) / (pEnd.x - pStart.x);
			}
			// point is right of rect
			else if (examineOutcode & 2) {
				x = rect.x + rect.width;
				y = pStart.y + (pEnd.y - pStart.y) * (rect.x + rect.width - pStart.x) / (pEnd.x - pStart.x);
			}

			// move the point under examination to the intersection point, then repeat
			if (examineOutcode == startOutcode){
				pStart.x = x;
				pStart.y = y;
				startOutcode = win::utils::findOutcode(rect, pStart.x, pStart.y);
			}
			else {
				pEnd.x = x;
				pEnd.y = y;
				endOutcode = win::utils::findOutcode(rect, pEnd.x, pEnd.y);
			}
		}
	}

	std::vector<win::Coords> returnCoords;
	returnCoords.push_back(pStart);
	returnCoords.push_back(pEnd);
	
	return returnCoords;
}

void DrawWindow::setStartCoord(win::Coords const startCoords)
{
	startCoord_ = startCoords;
}
