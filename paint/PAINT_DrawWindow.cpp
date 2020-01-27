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
	, activeColour_(gfx::Colour(255, 255, 255,255))
	, inactiveColour_(gfx::Colour(255, 255, 255, 255))
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

void DrawWindow::addClickedPixels(const int xMouse, const int yMouse)
{
	const Coords coord = { xMouse, yMouse };
	//std::cout << "Adding clicked pixel at x: " << xMouse << ", y: " << yMouse << '\n';
	clickedPixels_.push_back(coord);
}

void DrawWindow::swapActiveColour()
{
	std::swap(activeColour_, inactiveColour_);
}

/*override*/
void DrawWindow::draw()
{
	const auto& myRect = getRect();
	SDL_Rect destRect = { myRect.x, myRect.y, myRect.width, myRect.height };
	SDL_RenderCopy(renderer_, texture_, nullptr, &destRect);
}

void DrawWindow::mouseButtonDown(MouseButton const b, int const xPixel, int const yPixel)
{
	//Uint16* pixels = (Uint16*)surface_->pixels;            // Get the pixels from the Surface
	
	Coords mousePixel{ xPixel, yPixel };
	if (b == MouseButton::Left) {
		auto pixel = 0xFFFFFFFF; //uint32_t
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
//	// Iterate through the pixels and change the color
//	for (auto pixel : clickedPixels_) {
//		auto brushedArea = activeBrush.brushArea(pixel);
//		for (auto brushedPixel : brushedArea) {
//			pixels[brushedPixel.x + (brushedPixel.y * surface->w)] = SDL_MapRGB(surface->format, 255, 0, 0);
//		}
//
//	}
//
//}