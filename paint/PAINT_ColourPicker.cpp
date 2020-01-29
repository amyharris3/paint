#include "PAINT_ColourPicker.h"
#include "WIN_FreeLayout.h"
#include "WIN_TableLayout.h"
#include "PAINT_DrawWindow.h"
#include "WIN_Mouse.h"
#include <iostream>
#include "PAINT_ButtonFunctions.h"
#include "PAINT_Utils.h"

using namespace paint;

ColourPicker::ColourPicker(gfx::Rectangle rect, SDL_Renderer* renderer, std::shared_ptr<DrawWindow> const & drawWindow)
	: Container(std::make_shared<win::FreeLayout>(), rect, "colourPicker")
	, drawWindowPtr_(drawWindow)
	, renderer_(renderer)
	, displayBox_(std::make_shared<Container>(std::make_shared<win::TableLayout>(20, 20, 60, 0, 1, 2), gfx::Rectangle(rect.x, rect.y, rect.width, 70), "displayBox"))
	, primaryColourDisplay_(std::make_shared<win::ColourDisplay>(gfx::Rectangle(), "foregroundDisplay", std::make_shared<gfx::Colour>(drawWindow->getPrimaryColour()), renderer, true))
	, secondaryColourDisplay_(std::make_shared<win::ColourDisplay>(gfx::Rectangle(), "backgroundDisplay", std::make_shared<gfx::Colour>(drawWindow->getSecondaryColour()), renderer, false))
	, swapButton_(std::make_shared<win::Button>(renderer, gfx::Rectangle(rect.x + 75, rect.y + 20, 30, 30), "swapColourButton", "button_swap_colours.png", paint::swapColours))
	, clickDownOnColourDisplay_(false)
{
	addChild(swapButton_);
	
	displayBox_->addChild(primaryColourDisplay_);
	displayBox_->addChild(secondaryColourDisplay_);
	addChild(displayBox_);

	setDrawColour();
}

void ColourPicker::setDrawColour()
{
	if (primaryColourDisplay_->isActive()) {
		drawWindowPtr_->setDrawColourPrimary();
	}
	else if (secondaryColourDisplay_->isActive()) {
		drawWindowPtr_->setDrawColourSecondary();
	}
	else {
		std::cout << "Active colour not changed\n";
	}
}

void ColourPicker::swapActiveColour()
{
	primaryColourDisplay_->swapActive();
	secondaryColourDisplay_->swapActive();

	drawWindowPtr_->setPrimaryColour(primaryColourDisplay_->getForegroundColour());
	drawWindowPtr_->setSecondaryColour(secondaryColourDisplay_->getForegroundColour());

	setDrawColour();
}

void ColourPicker::updateFromDrawWindow()
{
	primaryColourDisplay_->updateColour(drawWindowPtr_->getPrimaryColour());
	secondaryColourDisplay_->updateColour(drawWindowPtr_->getSecondaryColour());
}

void ColourPicker::draw()
{
	//Background colour picker box
	SDL_Rect boxRect = { this->getRect().x, this->getRect().y, this->getRect().width, this->getRect().height };
	uint8_t rgba[4];
	getBackgroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);
	
	//update the colour displays to match colour setup in drawWindow
	primaryColourDisplay_->updateColour(drawWindowPtr_->getPrimaryColour());
	secondaryColourDisplay_->updateColour(drawWindowPtr_->getSecondaryColour());
	
	 for (auto const& child : getChildren())
	{
		child->draw();
	}
}

void ColourPicker::mouseButtonDown(win::MouseButton const button)
{
	std::cout << "Clicking down in ColourPicker area\n";
	/*auto xPixel = drawWindowPtr_->getMouseCoords().x;
	auto yPixel = drawWindowPtr_->getMouseCoords().y;
	//if (primaryColourDisplay_->getRect().containsPoint(xPixel + getRect().x, yPixel + getRect().y) || secondaryColourDisplay_->getRect().containsPoint(xPixel + getRect().x, yPixel + getRect().y))
	if (primaryColourDisplay_->getRect().containsPoint(xPixel, yPixel) || secondaryColourDisplay_->getRect().containsPoint(xPixel, yPixel))
	{
		clickDownOnColourDisplay_ = true;
		std::cout << "Clicking down in colour display area\n";
		//drawWindowPtr_->swapColours();
		//primaryColourDisplay_->updateColour();
		//secondaryColourDisplay_->updateColour();
	}*/
}

void ColourPicker::mouseButtonUp(win::MouseButton const button)
{
	std::cout << "Clicking up in ColourPicker area\n";
	/*auto xPixel = drawWindowPtr_->getMouseCoords().x;
	auto yPixel = drawWindowPtr_->getMouseCoords().y;
	if (clickDownOnColourDisplay_ == true) {
		std::cout << "Clicking up in ColourPicker area\n";
		if (primaryColourDisplay_->getRect().containsPoint(xPixel, yPixel) || secondaryColourDisplay_->getRect().containsPoint(xPixel, yPixel))
		{
			std::cout << "Clicking up in colour display area\n";
			primaryColourDisplay_->swapActive();
			secondaryColourDisplay_->swapActive();
			
			//drawWindowPtr_->swapColours();
			//primaryColourDisplay_->updateColour();
			//secondaryColourDisplay_->updateColour();
		}
		clickDownOnColourDisplay_ = false;
	}*/
}