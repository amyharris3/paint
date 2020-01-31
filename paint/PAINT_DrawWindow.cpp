#include "PAINT_DrawWindow.h"
#include <SDL.h>
#include "PAINT_Brush.h"
#include "WIN_Mouse.h"
#include "PAINT_DrawTool.h"
#include <WIN_ToggleButton.h>
#include "WIN_Coords.h"

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window( renderer, rect, name)
	, activeTool_(nullptr)
	, primaryColour_(gfx::Colour(255, 255, 255,255))
	, secondaryColour_(gfx::Colour(255, 255, 255, 255))
	, renderer_(renderer)
	, mouseCoords_({0,0})
	, prevMouseCoords_({0, 0})
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

/*override*/
void DrawWindow::mouseButtonDown(MouseButton const b)
{	
	const win::Coords rel = { mouseCoords_.x - this->getRect().x, mouseCoords_.y - this->getRect().y };
	const win::Coords prevRel = { prevMouseCoords_.x - this->getRect().x, prevMouseCoords_.y - this->getRect().y };
	
	if (b == MouseButton::Left) {
		if (activeTool_)
		{
			activeTool_->toolFunction(rel, prevRel);
		}
	}
}

/*override*/
void DrawWindow::mouseButtonUp(win::MouseButton const b)
{
	if (b == MouseButton::Left) {
		if (activeTool_)
		{
			activeTool_->clearLines();
		}
	}
}

void DrawWindow::setActiveTool(std::shared_ptr<Tool> tool)
{
	activeTool_ = tool;
}

void DrawWindow::toggleDrawTool(win::ToggleButton* b)
{
	if (b->getState() == ToggleButton::on) {
		activeTool_ = drawTool_;
	}
	else if (b->getState() == ToggleButton::off) {
		activeTool_ = nullptr;
	}
}

void DrawWindow::setMouseCoords(win::Coords relCoords)
{
	mouseCoords_ = relCoords;
}

void DrawWindow::setPrevCoords(win::Coords relPrevCoords)
{
	prevMouseCoords_ = relPrevCoords;
}

void DrawWindow::setPrimaryColour(gfx::Colour colour)
{
	primaryColour_ = colour;
}

void DrawWindow::setSecondaryColour(gfx::Colour colour)
{
	secondaryColour_ = colour;
}

/*override*/
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