#include "PAINT_DrawWindow.h"
#include <SDL.h>
#include "PAINT_Brush.h"
#include "WIN_Mouse.h"
#include <iostream>

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window( renderer, rect, name)
	, activeTool_(nullptr)
	, activeBrush_(nullptr)
	, primaryColour_(gfx::Colour(255, 255, 255,255))
	, secondaryColour_(gfx::Colour(255, 255, 255, 255))
	, name_(name)
	, renderer_(renderer)
	, drawToggle_(false)
{
	texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height);
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


void DrawWindow::setPrimaryColour(gfx::Colour colour)
{
	primaryColour_ = colour;
}

void DrawWindow::setSecondaryColour(gfx::Colour colour)
{
	secondaryColour_ = colour;
}

void DrawWindow::swapColours()
{
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
	//}
}

void DrawWindow::mouseButtonDown(MouseButton const b, int const xPixel, int const yPixel)
{
	//Uint16* pixels = (Uint16*)surface_->pixels;            // Get the pixels from the Surface
	
	Coords mousePixel{ xPixel, yPixel };
	if (b == MouseButton::Left) {
		if (drawToggle_) {
			//uint32_t pixel = 0xFFFFFFFF;
			SDL_Rect pixelRect = { xPixel, yPixel, 1, 1 };
			SDL_UpdateTexture(texture_, &pixelRect, reinterpret_cast<void*>(&pixel), 1);

		}

		//auto brushedArea = activeBrush_->brushArea(mousePixel);
		//for (auto brushedPixel : brushedArea) {
		//	std::cout << "brushed pixel at x: " << brushedPixel.x << ", y: " << brushedPixel.y << '\n';

		//	SDL_RenderDrawPoint(renderer_, brushedPixel.x, brushedPixel.y);
		//	
		//	//}
		//}
	}
}


void DrawWindow::toggleDraw()
{
	drawToggle_ = !drawToggle_;
}