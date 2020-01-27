#include "PAINT_ColourPicker.h"
#include "WIN_FreeLayout.h"
#include "WIN_TableLayout.h"
#include "PAINT_DrawWindow.h"

using namespace paint;

ColourPicker::ColourPicker::ColourPicker(gfx::Rectangle rect, SDL_Renderer* renderer, std::shared_ptr<DrawWindow> drawWindow)
	: Container(std::make_shared<win::FreeLayout>(), rect, "colourPicker")
	, renderer_(renderer)
	, displayBox_(std::make_shared<win::TableLayout>(20, 20, 20, 0, 1, 2), gfx::Rectangle(rect.x, rect.y, rect.width, 70), "displayBox")
	, fgDisplay_(std::make_shared<win::ColourDisplay>(gfx::Rectangle(), "foregroundDisplay", std::make_shared<gfx::Colour>(drawWindow->getPrimaryColour()), renderer, true))
	, bgDisplay_(std::make_shared<win::ColourDisplay>(gfx::Rectangle(), "backgroundDisplay", std::make_shared<gfx::Colour>(drawWindow->getSecondaryColour()), renderer, false))
{
	displayBox_.addChild(fgDisplay_);
	displayBox_.addChild(bgDisplay_);	
}

void ColourPicker::draw()
{
	//Background colour picker box
	SDL_Rect boxRect = { this->getRect().x, this->getRect().y, this->getRect().width, this->getRect().height };
	uint8_t rgba[4];
	getBackgroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);
	
	displayBox_.draw();
}