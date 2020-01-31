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
	, activeTool_(nullptr)
	, activeBrush_(nullptr)
	, name_(name)
	, primaryColour_(gfx::Colour(255, 255, 255,255))
	, secondaryColour_(gfx::Colour(255, 255, 255, 255))
	, renderer_(renderer)
	, drawToggle_(false)
{
	texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height);
	setDrawColourAsPrimary();
	//primaryColour_.getComponents(primaryRGBA_);
	//secondaryColour_.getComponents(secondaryRGBA_);
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

//void DrawWindow::getPixels(SDL_Surface* surface)
//{
//	pixels_ = surface->pixels;
//}

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

void DrawWindow::swapColours()
{
	std::cout << "Swapping colours\n";
	std::swap(primaryColour_, secondaryColour_);
	std::cout << "Colours have been swapped \n";
}

// Sets the active colour for drawing, defaults to primary
void DrawWindow::setDrawColourAsPrimary()
{
	primaryColour_.getComponents(drawRGBA_);
}

void DrawWindow::setDrawColourAsSecondary()
{
	secondaryColour_.getComponents(drawRGBA_);
}

void DrawWindow::setPrimaryAsDrawColour()
{
	setPrimaryColour(gfx::Colour(drawRGBA_[0], drawRGBA_[1], drawRGBA_[2], drawRGBA_[3]));
}

void DrawWindow::setSecondaryAsDrawColour()
{
	setSecondaryColour(gfx::Colour(drawRGBA_[0], drawRGBA_[1], drawRGBA_[2], drawRGBA_[3]));
}

/*override*/
void DrawWindow::draw()
{
	//if (drawingToggle_) {
	const auto& myRect = getRect();
	SDL_Rect destRect = { myRect.x, myRect.y, myRect.width, myRect.height };
	SDL_RenderCopy(renderer_, texture_, nullptr, &destRect);
	//SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderDrawColor(renderer_, int(drawRGBA_[0]), int(drawRGBA_[1]), int(drawRGBA_[2]), int(drawRGBA_[3]));
	for (std::vector<Line>::const_iterator i = lines_.begin(); i != lines_.end(); ++i) {
		Line line = *i;
		SDL_RenderDrawLine(renderer_, line.x1, line.y1, line.x2, line.y2);
	}
	//}
}

bool DrawWindow::mouseButtonDown(MouseButton b)
{
	//Uint16* pixels = (Uint16*)surface_->pixels;            // Get the pixels from the Surface

	//const int xRel = mouseCoords_.x - this->getRect().x;
	//const int yRel = mouseCoords_.y - this->getRect().y;
	//const int xPrevRel = prevMouseCoords_.x - this->getRect().x;
	//const int yPrevRel = prevMouseCoords_.y - this->getRect().y;

	if (b == MouseButton::Left) {
		if (drawToggle_) {
			lines_.push_back({ mouseCoords_.x, mouseCoords_.y, prevMouseCoords_.x, prevMouseCoords_.y });

			//uint32_t pixel = 0xFFFFFFFF;
			//SDL_Rect pixelRect = { xRel, yRel, 1, 1 };
			//SDL_UpdateTexture(texture_, &pixelRect, reinterpret_cast<void*>(&pixel), 1);


		}

		//auto brushedArea = activeBrush_->brushArea(mousePixel);
		//for (auto brushedPixel : brushedArea) {
		//	std::cout << "brushed pixel at x: " << brushedPixel.x << ", y: " << brushedPixel.y << '\n';

		//	SDL_RenderDrawPoint(renderer_, brushedPixel.x, brushedPixel.y);
		//	
		//	//}
		//}
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
