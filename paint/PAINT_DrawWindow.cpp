#include "PAINT_DrawWindow.h"
#include <SDL.h>
#include "PAINT_Brush.h"
#include "WIN_Mouse.h"
#include <iostream>
#include "PAINT_Utils.h"

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window( renderer, rect, name)
	, activeBrush_(nullptr)
	, primaryColour_(gfx::Colour(255, 255, 255,255))
	, secondaryColour_(gfx::Colour(255, 255, 255, 255))
	, renderer_(renderer)
	, drawToggle_(false)
	, mouseCoords_({0,0})
	, prevMouseCoords_({0,0})
	, primaryActive_(true)
	, primaryRGBA_{}
	, secondaryRGBA_{}
{
	texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height);
	primaryColour_.getComponents(primaryRGBA_);
	secondaryColour_.getComponents(secondaryRGBA_);
} 

DrawWindow::~DrawWindow()
{
	if (texture_) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
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
	//if (drawingToggle_) {
	const auto& myRect = getRect();
	SDL_Rect destRect = { myRect.x, myRect.y, myRect.width, myRect.height };
	SDL_RenderCopy(renderer_, texture_, nullptr, &destRect);
	//SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);

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
	
	SDL_SetRenderDrawColor(renderer_, int(drawRGBA_[0]), int(drawRGBA_[1]), int(drawRGBA_[2]), int(drawRGBA_[3]));
	//for (std::vector<Line>::const_iterator i = lines_.begin(); i != lines_.end(); ++i) {
	for (auto line : lines_) {
		SDL_RenderDrawLine(renderer_, line.x1, line.y1, line.x2, line.y2);
	}
	//}
}

void DrawWindow::updateAndRerender()
{
	draw();
	SDL_RenderPresent(renderer_);
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
	const auto& myRect = getRect();
	SDL_Rect destRect = { myRect.x, myRect.y, myRect.width, myRect.height };
	SDL_RenderCopy(renderer_, texture_, nullptr, &destRect);
}
