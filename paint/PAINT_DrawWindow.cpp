#include "PAINT_DrawWindow.h"
#include <SDL.h>
#include <iostream> 
#include "PAINT_Brush.h"
#include "WIN_Mouse.h"

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, gfx::Rectangle const & rect, const char* name)
	: Window(sdlWindow, renderer, surface, rect, name)
	,  activeTool_(nullptr)
	, name_(nullptr)
	, surface_(surface)
{
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


void DrawWindow::mouseButtonDown(MouseButton b, int xPixel, int yPixel)
{
	Uint16* pixels = (Uint16*)surface_->pixels;            // Get the pixels from the Surface
	
	Coords mousePixel{ xPixel, yPixel };
	if (b == MouseButton::Left) {
		//std::cout << "Mouse clicked in draw window! \n";
			// Iterrate through the pixels and change the color
		//for (auto pixel : clickedPixels_) {
		//	std::cout << "painty paint \n";
		auto brushedArea = activeBrush_->brushArea(mousePixel);
		for (auto brushedPixel : brushedArea) {
			std::cout << "brushed pixel at x: " << brushedPixel.x << ", y: " << brushedPixel.y << '\n';
			pixels[brushedPixel.x + (brushedPixel.y * surface_->w)] = SDL_MapRGB(surface_->format, 24, 134, 22);
			//}
		}
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