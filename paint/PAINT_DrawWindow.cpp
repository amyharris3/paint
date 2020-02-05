#include "PAINT_DrawWindow.h"
#include "PAINT_Brush.h"
#include "WIN_Mouse.h"
#include <iostream>
#include "PAINT_Utils.h"
#include "GFX_Line.h"

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(gfx::Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window( renderer, rect, name)
	, renderer_(renderer)
	, activeTool_(nullptr)
	, activeBrush_(nullptr)
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
} 

DrawWindow::~DrawWindow()
{
	renderer_->destroyDrawWindowTexture();
}


void DrawWindow::setActiveBrush(Brush* brush)
{	
	activeBrush_ = brush;
}

void DrawWindow::setMouseCoords(Coords relCoords)
{
	mouseCoords_ = relCoords;
}

void DrawWindow::setPrevCoords(Coords relPrevCoords)
{
	prevMouseCoords_ = relPrevCoords;
}

void DrawWindow::setPrimaryColour(gfx::Colour colour)
{
	primaryColour_ = colour;
	primaryColour_.getComponents(primaryRGBA_);
}

void DrawWindow::setSecondaryColour(gfx::Colour colour)
{
	secondaryColour_ = colour;
	secondaryColour_.getComponents(secondaryRGBA_);
}

void DrawWindow::swapPrimarySecondaryColours()
{
	std::cout << "Swapping colours\n";
	std::swap(primaryColour_, secondaryColour_);
	std::cout << "Colours have been swapped \n";
}

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

bool DrawWindow::mouseButtonDown(const MouseButton button)
{
	
	if (button == MouseButton::Left) {
		if (drawToggle_) {
			lines_.push_back({ mouseCoords_.x, mouseCoords_.y, prevMouseCoords_.x, prevMouseCoords_.y });

		}

	}
	return true;
}


void DrawWindow::toggleDraw()
{
	drawToggle_ = !drawToggle_;
}

// TODO Needs more work, to properly clear drawWindow
void DrawWindow::clearScreen() const
{
	renderer_->clearDrawWindow(getRect());
}
