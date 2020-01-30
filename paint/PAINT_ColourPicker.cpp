#include "PAINT_ColourPicker.h"
#include "WIN_FreeLayout.h"
#include "WIN_TableLayout.h"
#include "PAINT_DrawWindow.h"
#include "WIN_Mouse.h"
#include <iostream>
#include "PAINT_ButtonFunctions.h"
#include "PAINT_Utils.h"
#include "WIN_ColourValueTextbox.h"

using namespace paint;

ColourPicker::ColourPicker(gfx::Rectangle rect, SDL_Renderer* renderer, std::shared_ptr<DrawWindow> const & drawWindow)
	: Container(std::make_shared<win::FreeLayout>(), rect, "colourPicker")
	, drawWindowPtr_(drawWindow)
	, renderer_(renderer)
	, displayBox_(std::make_shared<Container>(std::make_shared<win::TableLayout>(20, 20, 60, 0, 1, 2), gfx::Rectangle(rect.x, rect.y, rect.width, 70), "displayBox"))
	, primaryColourDisplay_(std::make_shared<win::ColourDisplay>(gfx::Rectangle(), "primaryColourDisplay", drawWindow->getPrimaryRGBA(), renderer, true))
	, secondaryColourDisplay_(std::make_shared<win::ColourDisplay>(gfx::Rectangle(), "secondaryColourDisplay",drawWindow-> getSecondaryRGBA(), renderer, false))
	, swapButton_(std::make_shared<win::Button>(renderer, gfx::Rectangle(rect.x + 75, rect.y + 20, 30, 30), "swapColourButton", "button_swap_colours.png", paint::swapColours))
	, colourValuesBox_(std::make_shared<Container>(std::make_shared<win::TableLayout>(0, 0, 0, 20, 4, 1), gfx::Rectangle(rect.x + rect.width - 50, rect.y + 65, 40, 140), "colourValuesBox"))
	, swappedDisplays_(false)
{
	addChild(swapButton_);
	
	displayBox_->addChild(primaryColourDisplay_);
	displayBox_->addChild(secondaryColourDisplay_);
	addChild(displayBox_);

	redValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "redValueBox", renderer, 18, 2, -3, drawWindowPtr_->getDrawRed());
	redValueBox_->setBackgroundColour({ 255,50,50,200 });
	greenValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "greenValueBox", renderer, 18, 2, -3, drawWindowPtr_->getDrawGreen());
	greenValueBox_->setBackgroundColour({ 50,255,50,200 });
	blueValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "blueValueBox", renderer, 18, 2, -3, drawWindowPtr_->getDrawBlue());
	blueValueBox_->setBackgroundColour({ 50, 50, 255, 200 });
	alphaValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "alphaValueBox", renderer, 18, 2, -3, drawWindowPtr_->getDrawAlpha());
	alphaValueBox_->setBackgroundColour({ 150,150,150,200 });
	
	colourValuesBox_->addChild(redValueBox_);
	colourValuesBox_->addChild(greenValueBox_);
	colourValuesBox_->addChild(blueValueBox_);
	colourValuesBox_->addChild(alphaValueBox_);

	addChild(colourValuesBox_);

	setDrawColourFromActive();
}

void ColourPicker::setDrawColourFromActive() const
{
	if (primaryColourDisplay_->isActive() && secondaryColourDisplay_->isActive()){
		printf("Error: both colours defined as active\n");
	}
	else if (primaryColourDisplay_->isActive()) {
		printf("Draw colour is primary\n");
		drawWindowPtr_->setDrawColourAsPrimary();
	}
	else if (secondaryColourDisplay_->isActive()) {
		printf("Draw colour is secondary\n");
		drawWindowPtr_->setDrawColourAsSecondary();
	}
	else {
		std::cout << "Active colour not changed\n";
	}
}

void ColourPicker::setPrimarySecondaryFromActiveDraw() const
{
	if (primaryColourDisplay_->isActive() && secondaryColourDisplay_->isActive()) {
		printf("Error: both colours defined as active\n");
	}
	else if (primaryColourDisplay_->isActive()) {
		drawWindowPtr_->setPrimaryAsDrawColour();
	}
	else if (secondaryColourDisplay_->isActive()) {
		drawWindowPtr_->setSecondaryAsDrawColour();
	}
}

void ColourPicker::updateColourValueBoxes() const
{
	printf("Updating RGBA\n");
	redValueBox_->valueChangedExternally();
	greenValueBox_->valueChangedExternally();
	blueValueBox_->valueChangedExternally();
	alphaValueBox_->valueChangedExternally();
}

void ColourPicker::swapActiveColour()
{
	primaryColourDisplay_->swapIsActive();
	secondaryColourDisplay_->swapIsActive();

	setDrawColourFromActive();
	updateColourValueBoxes();
}

void ColourPicker::updateColourDisplaysFromDrawWindow()
{
	if (swappedDisplays_) {
		primaryColourDisplay_->updateColour(drawWindowPtr_->getPrimaryColour());
		secondaryColourDisplay_->updateColour(drawWindowPtr_->getSecondaryColour());
	}
	else{
		primaryColourDisplay_->updateColour(drawWindowPtr_->getSecondaryColour());
		secondaryColourDisplay_->updateColour(drawWindowPtr_->getPrimaryColour()); 
	}
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
			primaryColourDisplay_->swapIsActive();
			secondaryColourDisplay_->swapIsActive();
			
			//drawWindowPtr_->swapColours();
			//primaryColourDisplay_->updateColour();
			//secondaryColourDisplay_->updateColour();
		}
		clickDownOnColourDisplay_ = false;
	}*/
}