#include "PAINT_DrawWindow.h"
#include <SDL.h>
#include <iostream> 
#include "PAINT_Brush.h"
#include "WIN_Mouse.h"

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, gfx::Rectangle const& rect, const char* name)
	: Window(sdlWindow, renderer, surface, rect, name)
	, activeTool_(nullptr)
	, activeBrush_(nullptr)
	, name_(nullptr)
	, surface_(surface)
	, renderer_(renderer)
	, texture_(nullptr)
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

void DrawWindow::AddClickedPixels(int xMouse, int yMouse)
{
	Coords coord = { xMouse, yMouse };
	//std::cout << "Adding clicked pixel at x: " << xMouse << ", y: " << yMouse << '\n';
	clickedPixels_.push_back(coord);
}

/*override*/
void DrawWindow::draw()
{
	const auto& myRect = getRect();
	SDL_Rect destRect = { myRect.x, myRect.y, myRect.width, myRect.height };
	SDL_RenderCopy(renderer_, texture_, nullptr, &destRect);
}

void DrawWindow::mouseButtonDown(MouseButton b, int xPixel, int yPixel)
{
	//Uint16* pixels = (Uint16*)surface_->pixels;            // Get the pixels from the Surface
	
	Coords mousePixel{ xPixel, yPixel };
	if (b == MouseButton::Left) {
		uint32_t pixel = 0xFFFFFFFF;
		SDL_Rect pixelRect = { xPixel, yPixel, 1, 1 };
		SDL_UpdateTexture(texture_, &pixelRect, reinterpret_cast<void*>(&pixel), 1);
		//auto brushedArea = activeBrush_->brushArea(mousePixel);
		//for (auto brushedPixel : brushedArea) {
		//	std::cout << "brushed pixel at x: " << brushedPixel.x << ", y: " << brushedPixel.y << '\n';

		//	SDL_RenderDrawPoint(renderer_, brushedPixel.x, brushedPixel.y);
		//	
		//	//}
		//}
	}
}

//void DrawWindow::setColor(SDL_Surface* surface)
//{
//	Uint16* pixels = (Uint16*)surface->pixels;            // Get the pixels from the Surface
//
//	// Iterrate through the pixels and change the color
//	for (auto pixel : clickedPixels_) {
//		auto brushedArea = activeBrush.brushArea(pixel);
//		for (auto brushedPixel : brushedArea) {
//			pixels[brushedPixel.x + (brushedPixel.y * surface->w)] = SDL_MapRGB(surface->format, 255, 0, 0);
//		}
//
//	}
//
//}