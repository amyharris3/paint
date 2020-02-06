#include "PAINT_pch.h"
#include "PAINT_DrawWindow.h"
#include "WIN_Mouse.h"
#include "PAINT_DrawTool.h"
#include "WIN_ToggleButton.h"
#include "WIN_Coords.h"
#include "WIN_ButtonStates.h"

using namespace paint;
using namespace win;

DrawWindow::DrawWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name)
	, activeTool_(nullptr)
	, primaryColour_(gfx::Colour(255, 255, 255, 255))
	, secondaryColour_(gfx::Colour(255, 255, 255, 255))
	, renderer_(renderer)
	, mouseCoords_({ 0,0 })
	, prevMouseCoords_({ 0,0 })
	, primaryActive_(true)
	, primaryRGBA_{}
	, secondaryRGBA_{}
{
	texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.width, rect.height);
	primaryColour_.getComponents(primaryRGBA_);
	secondaryColour_.getComponents(secondaryRGBA_);
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

void DrawWindow::swapPrimarySecondaryColours()
{
	std::cout << "Swapping colours\n";
	std::swap(primaryColour_, secondaryColour_);
	std::cout << "Colours have been swapped \n";
}

/*override*/
void DrawWindow::draw()
{
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
}

void DrawWindow::updateAndRerender()
{
	draw();
	SDL_RenderPresent(renderer_);
}

// TODO Needs more work, to properly clear drawWindow
void DrawWindow::clearScreen() const
{
	const auto& myRect = getRect();
	SDL_Rect destRect = { myRect.x, myRect.y, myRect.width, myRect.height };
	SDL_RenderCopy(renderer_, texture_, nullptr, &destRect);
}
