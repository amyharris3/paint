#include "PAINT_pch.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_Brush.h"
#include "WIN_Mouse.h"
#include "PAINT_DrawTool.h"
#include "WIN_ToggleButton.h"
#include "WIN_Coords.h"
#include "WIN_ButtonStates.h"
#include "PAINT_Utils.h"
#include "GFX_Line.h"
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
	, drawToggle_(false)
	, mouseCoords_({0,0})
	, prevMouseCoords_({0,0})
	, primaryActive_(true)
	, primaryRGBA_{}
	, secondaryRGBA_{}
{
	//texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height);
	renderer_->createDrawWindowTexture(rect);
	primaryColour_.getComponents(primaryRGBA_);
	secondaryColour_.getComponents(secondaryRGBA_);
	auto test = getBackgroundColour();
}

DrawWindow::~DrawWindow()
{
	renderer_->destroyDrawWindowTexture();
}

/*override*/

//if exit, mouse may move too fast for render lines to keep up, so must interpolate intersect with DW boundary
bool DrawWindow::mouseExit()
{
	int xMouse = mouseCoords_.x;
	int yMouse = mouseCoords_.y;
	SDL_GetMouseState(&xMouse, &yMouse);
	auto absCoords = clippingHandler(prevMouseCoords_, { xMouse, yMouse });

	prevMouseCoords_ = { absCoords[0].x, absCoords[0].y};
	mouseCoords_ = { absCoords[1].x, absCoords[1].y };

	if (drawToggle_) {
		if (activeTool_) {
			const Coords prevRel = { prevMouseCoords_.x - this->getRect().x, prevMouseCoords_.y - this->getRect().y };
			const Coords rel = { mouseCoords_.x - this->getRect().x, mouseCoords_.y - this->getRect().y };

			activeTool_->toolFunction(rel, prevRel);
		}
	}
	
	return false;
}

bool DrawWindow::mouseButtonDown(MouseButton const b)
{
	drawToggle_ = true;
	if (b == MouseButton::Left) {
		if (activeTool_) {
			const Coords prevRel = { prevMouseCoords_.x - this->getRect().x, prevMouseCoords_.y - this->getRect().y };
			const Coords rel = { mouseCoords_.x - this->getRect().x, mouseCoords_.y - this->getRect().y };

			activeTool_->toolFunction(rel, prevRel);
		}
	}

	return false;
}

/*override*/
bool DrawWindow::mouseButtonUp(win::MouseButton const b)
{
	drawToggle_ = false;
	if (b == MouseButton::Left) {
		if (activeTool_) {
			activeTool_->clearLines();
		}
	}

	return false;
}

void DrawWindow::setActiveTool(std::shared_ptr<Tool> tool)
{
	activeTool_ = std::move(tool);
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

void DrawWindow::toggleDrawTool(win::ToggleButton* b)
{
	if (b->getState() == ButtonStates::on) {
		activeTool_ = drawTool_;
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

void DrawWindow::setCanvasColour(gfx::Colour colour)
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

//void DrawWindow::swapPrimarySecondaryColours()
//{
//	std::cout << "Swapping colours\n";
//	std::swap(primaryColour_, secondaryColour_);
//	std::cout << "Colours have been swapped \n";
//}

/*override*/
void DrawWindow::draw()
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
	
	renderer_->renderDrawWindow(getRect(), drawRGBA_, lines_);
}

void DrawWindow::updateAndRerender()
{
	draw();
	renderer_->renderPresent();
}

// TODO Needs more work, to properly clear drawWindow
void DrawWindow::clearWindow() const
{
	renderer_->clearDrawWindow(getRect(), getBackgroundColour());
}

//using Cohen-Sutherland clipping algorithm
std::vector<win::Coords> DrawWindow::clippingHandler(win::Coords pStart, win::Coords pEnd)
{
	bool accept = false;
	const auto rect = getRect();
	
	int startOutcode = win::utils::findOutcode(rect, pStart.x, pStart.y);
	int endOutcode = win::utils::findOutcode(rect, pEnd.x, pEnd.y);

	printf("1: (%d,%d), 2: (%d,%d) -> ", pStart.x, pStart.y, pEnd.x, pEnd.y);
	
	while(true){
		// case where start and end points are within rectangle
		if (!(startOutcode | endOutcode)){
			printf("both inside DW\n");
			accept = true;
			break;
		}
		// both points share one zone designation outside the rect, so no crossing over into the rect
		else if (startOutcode & endOutcode) {
			break;
		}
		// one or more point is outside rect and not sharing 'outside zone'
		else {
			printf("start (%d,%d), end (%d,%d)\n", pStart.x, pStart.y, pEnd.x, pEnd.y);
			// if startOutcode is 0, ie false, then is inside rect, so examine pEnd instead
			auto examineOutcode = startOutcode ? startOutcode : endOutcode;
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
			printf("point %d, %d\n", x, y);
		}
	}

	std::vector<win::Coords> returnCoords;
	returnCoords.push_back(pStart);
	returnCoords.push_back(pEnd);
	
	return returnCoords;
}