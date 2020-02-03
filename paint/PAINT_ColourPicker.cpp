#include "PAINT_ColourPicker.h"
#include "WIN_FreeLayout.h"
#include "WIN_TableLayout.h"
#include "PAINT_DrawWindow.h"
#include "WIN_Mouse.h"
#include <iostream>
#include "PAINT_ButtonFunctions.h"
#include "PAINT_Utils.h"
#include "WIN_ColourValueTextbox.h"
#include <cassert>

using namespace paint;

ColourPicker::ColourPicker(gfx::Rectangle rect, SDL_Renderer* renderer, std::shared_ptr<DrawWindow> const & drawWindow)
	: Container(std::make_shared<win::FreeLayout>(), rect, "colourPicker")
	, drawWindowPtr_(drawWindow)
	, renderer_(renderer)
	, displayBox_(std::make_shared<Container>(std::make_shared<win::TableLayout>(20, 20, 60, 0, 1, 2), gfx::Rectangle(rect.x, rect.y, rect.width, 70), "displayBox"))
	, primaryColourDisplay_(std::make_shared<win::ColourDisplay>(gfx::Rectangle(), "primaryColourDisplay", drawWindow->getPrimaryRGBA(), renderer, true))
	, secondaryColourDisplay_(std::make_shared<win::ColourDisplay>(gfx::Rectangle(), "secondaryColourDisplay",drawWindow-> getSecondaryRGBA(), renderer, false))
	, swapButton_(std::make_shared<win::Button>(renderer, gfx::Rectangle(rect.x + 75, rect.y + 20, 30, 30), "swapColourButton", "button_swap_colours.png", paint::swapColours))
	, swappedDisplays_(false)
	, colourValuesBox_(std::make_shared<Container>(std::make_shared<win::TableLayout>(0, 0, 0, 20, 4, 1), gfx::Rectangle(rect.x + rect.width - 50, rect.y + 65, 40, 140), "colourValuesBox"))
	, colourSliders_(std::make_shared<Container>(std::make_shared<win::TableLayout>(0, 0, 0, 20, 4, 1), gfx::Rectangle(rect.x+5, rect.y + 65, 120, 140), "colourSlidersBox"))
{
	addChild(swapButton_);
	
	initialiseColourDisplays();
	initialiseColourValueBoxes();
	initialiseColourSliders();
	
	setDrawColourFromActive();
	updateColourSliders();
}

inline void ColourPicker::initialiseColourDisplays()
{

	displayBox_->addChild(primaryColourDisplay_);
	displayBox_->addChild(secondaryColourDisplay_);
	addChild(displayBox_);
}

inline void ColourPicker::initialiseColourValueBoxes()
{
	redValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "redValueBox", renderer_, 18, 2, -3, drawWindowPtr_->getDrawRed());
	redValueBox_->setBackgroundColour({ 255,50,50,200 });
	greenValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "greenValueBox", renderer_, 18, 2, -3, drawWindowPtr_->getDrawGreen());
	greenValueBox_->setBackgroundColour({ 50,255,50,200 });
	blueValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "blueValueBox", renderer_, 18, 2, -3, drawWindowPtr_->getDrawBlue());
	blueValueBox_->setBackgroundColour({ 50, 50, 255, 200 });
	alphaValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "alphaValueBox", renderer_, 18, 2, -3, drawWindowPtr_->getDrawAlpha());
	alphaValueBox_->setBackgroundColour({ 150,150,150,200 });
	
	colourValuesBox_->addChild(redValueBox_);
	colourValuesBox_->addChild(greenValueBox_);
	colourValuesBox_->addChild(blueValueBox_);
	colourValuesBox_->addChild(alphaValueBox_);
	addChild(colourValuesBox_);
}


inline void ColourPicker::initialiseColourSliders()
{
	redValueSlider_ = std::make_shared<win::ColourSlider>(renderer_, gfx::Rectangle(15, 660, 105, 20), "redValueSlider", gfx::Colour(255, 255, 255, 255), gfx::Colour(0, 0, 0, 255), drawWindowPtr_->getDrawRed());
	greenValueSlider_ = std::make_shared<win::ColourSlider>(renderer_, gfx::Rectangle(15, 660, 105, 20), "greenValueSlider", gfx::Colour(255, 255, 255, 255), gfx::Colour(0, 0, 0, 255), drawWindowPtr_->getDrawGreen());
	blueValueSlider_ = std::make_shared<win::ColourSlider>(renderer_, gfx::Rectangle(15, 660, 105, 20), "blueValueSlider", gfx::Colour(255, 255, 255, 255), gfx::Colour(0, 0, 0, 255), drawWindowPtr_->getDrawBlue());
	alphaValueSlider_ = std::make_shared<win::ColourSlider>(renderer_, gfx::Rectangle(15, 660, 105, 20), "alphaValueSlider", gfx::Colour(255, 255, 255, 255), gfx::Colour(0, 0, 0, 255), drawWindowPtr_->getDrawAlpha());

	colourSliders_->addChild(redValueSlider_);
	colourSliders_->addChild(greenValueSlider_);
	colourSliders_->addChild(blueValueSlider_);
	colourSliders_->addChild(alphaValueSlider_);
	addChild(colourSliders_);
	colourSliders_->applyLayout();
	redValueSlider_->updateLineMarker();
	greenValueSlider_->updateLineMarker();
	blueValueSlider_->updateLineMarker();
	alphaValueSlider_->updateLineMarker();

}

void ColourPicker::setDrawColourFromActive() const
{
	assert(primaryColourDisplay_->isActive() != secondaryColourDisplay_->isActive());
	if (primaryColourDisplay_->isActive()) {
		drawWindowPtr_->setDrawColourAsPrimary();
	}
	else if (secondaryColourDisplay_->isActive()) {
		drawWindowPtr_->setDrawColourAsSecondary();
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


void ColourPicker::swapActiveColour() const
{
	primaryColourDisplay_->swapIsActive();
	secondaryColourDisplay_->swapIsActive();

	setDrawColourFromActive();
}

void ColourPicker::updateColourDisplaysFromDrawWindow() const
{
	const auto primaryRGBA = drawWindowPtr_->getPrimaryRGBA();
	const auto secondaryRGBA = drawWindowPtr_->getSecondaryRGBA();
	if (!swappedDisplays_) {
		primaryColourDisplay_->setColour(gfx::Colour(primaryRGBA[0], primaryRGBA[1], primaryRGBA[2], primaryRGBA[3]));
		secondaryColourDisplay_->setColour(gfx::Colour(secondaryRGBA[0], secondaryRGBA[1], secondaryRGBA[2], secondaryRGBA[3]));
	}
	else {
		primaryColourDisplay_->setColour(gfx::Colour(secondaryRGBA[0], secondaryRGBA[1], secondaryRGBA[2], secondaryRGBA[3]));
		secondaryColourDisplay_->setColour(gfx::Colour(primaryRGBA[0], primaryRGBA[1], primaryRGBA[2], primaryRGBA[3]));
	}
}

void ColourPicker::updateColourDisplays() const
{
	setPrimarySecondaryFromActiveDraw();
	primaryColourDisplay_->draw();
	secondaryColourDisplay_->draw();
}

void ColourPicker::updateColourValueBoxes() const
{
	redValueBox_->valueChangedExternally();
	greenValueBox_->valueChangedExternally();
	blueValueBox_->valueChangedExternally();
	alphaValueBox_->valueChangedExternally();
}

void ColourPicker::updateColourSliders() const
{
	redValueSlider_->valueChangedExternally();
	greenValueSlider_->valueChangedExternally();
	blueValueSlider_->valueChangedExternally();
	alphaValueSlider_->valueChangedExternally();
}

void ColourPicker::update()
{
	updateColourDisplays();
	updateColourValueBoxes();
	updateColourSliders();
}

void ColourPicker::updateAndRerender()
{
	update();
	
	draw();
	SDL_RenderPresent(renderer_);
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
	primaryColourDisplay_->setColour(drawWindowPtr_->getPrimaryColour());
	secondaryColourDisplay_->setColour(drawWindowPtr_->getSecondaryColour());
	
	 for (auto const& child : getChildren())
	{
		child->draw();
	}
}