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
bool DrawWindow::mouseButtonDown(MouseButton const b)
{
	const Coords rel = { mouseCoords_.x - this->getRect().x, mouseCoords_.y - this->getRect().y };
	const Coords prevRel = { prevMouseCoords_.x - this->getRect().x, prevMouseCoords_.y - this->getRect().y };

	if (b == MouseButton::Left) {
		if (activeTool_) {
			activeTool_->toolFunction(rel, prevRel);
		}
	}

	return false;
}

/*override*/
bool DrawWindow::mouseButtonUp(win::MouseButton const b)
{
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


