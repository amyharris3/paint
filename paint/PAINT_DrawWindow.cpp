#include "PAINT_DrawWindow.h"
#include <SDL.h>
#include "PAINT_Brush.h"
#include "WIN_Mouse.h"
#include "PAINT_DrawTool.h"

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window( renderer, rect, name)
	, activeTool_(nullptr)
	, primaryColour_(gfx::Colour(255, 255, 255,255))
	, secondaryColour_(gfx::Colour(255, 255, 255, 255))
	, name_(name)
	, renderer_(renderer)
{
	texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height);
	drawTool_ = std::make_shared<DrawTool>(renderer_, texture_);
}




DrawWindow::~DrawWindow()
{
	if (texture_) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}


//void DrawWindow::setActiveBrush(std::shared_ptr<Brush> brush)
//{	
//	activeBrush_ = brush;
//}

void DrawWindow::setActiveTool(std::shared_ptr<Tool> tool)
{
	activeTool_ = tool;
}

void DrawWindow::activateDrawTool()
{
	if (activeTool_ != drawTool_)
	{
		activeTool_ = drawTool_;
	}
	else
	{
		activeTool_ = nullptr;
	}



}

void DrawWindow::setMouseCoords(Coords relCoords)
{
	mouseCoords_ = relCoords;
}

void DrawWindow::setPrevCoords(Coords relPrevCoords)
{
	prevMouseCoords_ = relPrevCoords;
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
}

/*override*/
void DrawWindow::draw()
{

	const auto& myRect = getRect();	
	SDL_Rect destRect = { myRect.x, myRect.y, myRect.width, myRect.height };
	SDL_RenderCopy(renderer_, texture_, nullptr, &destRect);

}

void DrawWindow::mouseButtonDown(MouseButton b)
{
	//Uint16* pixels = (Uint16*)surface_->pixels;            // Get the pixels from the Surface
	
	const Coords rel = { mouseCoords_.x - this->getRect().x, mouseCoords_.y - this->getRect().y };
	const Coords prevRel = { prevMouseCoords_.x - this->getRect().x, prevMouseCoords_.y - this->getRect().y };
	
	if (b == MouseButton::Left) {
		if (activeTool_)
		{
			activeTool_->toolFunction(rel, prevRel);
		}

			

			//uint32_t pixel = 0xFFFFFFFF;
			//SDL_Rect pixelRect = { xRel, yRel, 1, 1 };
			//SDL_UpdateTexture(texture_, &pixelRect, reinterpret_cast<void*>(&pixel), 1);
			

	}

}

void DrawWindow::mouseButtonUp(win::MouseButton b)
{

	if (b == MouseButton::Left) {
		if (activeTool_)
		{
			//activeTool_->writeToTexture();
			//SDL_Rect drawRect = { this->getRect().x, this->getRect().y, this->getRect().width, this->getRect().height };
			//SDL_RenderCopy(renderer_, texture_, NULL, &drawRect);
			//SDL_RenderPresent(renderer_);
			activeTool_->clearLines();
		}

	}
}


