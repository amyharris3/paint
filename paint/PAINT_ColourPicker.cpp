#include "PAINT_pch.h"
#include "PAINT_ColourPicker.h"
#include "WIN_FreeLayout.h"
#include "WIN_TableLayout.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_ButtonFunctions.h"
#include "PAINT_Utils.h"
#include "WIN_ColourValueTextbox.h"
#include <cassert>
#include <utility>
#include "PAINT_ColourDisplay.h"

using namespace win;
using namespace paint;

ColourPicker::ColourPicker(gfx::Rectangle rect, gfx::Renderer* renderer, std::shared_ptr<DrawWindow> drawWindow)
	: Container(std::make_shared<win::FreeLayout>(), rect, "colourPicker")
	, drawWindowPtr_(std::move(drawWindow))
	, renderer_(renderer)
	, displayBox_(std::make_shared<win::Container>(std::make_shared<win::TableLayout>(20, 20, 60, 0, 1, 2), gfx::Rectangle(rect.x, rect.y, rect.width, 70), "displayBox"))
	, swapButton_(std::make_shared<win::Button>(renderer, gfx::Rectangle(rect.x + 75, rect.y + 20, 30, 30), "swapColourButton", "button_swap_colours.png", paint::swapColours))
	, swappedDisplays_(false)
	, colourValuesBox_(std::make_shared<win::Container>(std::make_shared<win::TableLayout>(0, 0, 0, 20, 4, 1), gfx::Rectangle(rect.x + rect.width - 50, rect.y + 65, 40, 140), "colourValuesBox"))
	, colourSliders_(std::make_shared<win::Container>(std::make_shared<win::TableLayout>(0, 0, 0, 20, 4, 1), gfx::Rectangle(rect.x+5, rect.y + 65, 120, 140), "colourSlidersBox"))
{
	addChild(swapButton_);
	
	initialiseColourDisplays();
	initialiseColourValueBoxes();
	initialiseColourSliders();
	
	setActiveColourInDrawWindow();
	updateColourSliders();
}

inline void ColourPicker::initialiseColourDisplays()
{
	leftColourDisplay_ = std::make_shared<ColourDisplay>(gfx::Rectangle(), "primaryColourDisplay", drawWindowPtr_->getPrimaryRGBA(), renderer_, true);
	rightColourDisplay_ = std::make_shared<ColourDisplay>(gfx::Rectangle(), "secondaryColourDisplay", drawWindowPtr_->getSecondaryRGBA(), renderer_, false);

	displayBox_->addChild(leftColourDisplay_);
	displayBox_->addChild(rightColourDisplay_);
	addChild(displayBox_);
}

inline void ColourPicker::initialiseColourValueBoxes()
{
	redValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "redValueBox", renderer_, 18, 2, -3, &(drawWindowPtr_->getPrimaryRGBA()[0]), &(drawWindowPtr_->getSecondaryRGBA()[0]), drawWindowPtr_->isPrimaryActive());
	redValueBox_->setBackgroundColour({ 255,50,50,200 });
	greenValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "greenValueBox", renderer_, 18, 2, -3, &(drawWindowPtr_->getPrimaryRGBA()[1]), &(drawWindowPtr_->getSecondaryRGBA()[1]), drawWindowPtr_->isPrimaryActive());
	greenValueBox_->setBackgroundColour({ 50,255,50,200 });
	blueValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "blueValueBox", renderer_, 18, 2, -3, &(drawWindowPtr_->getPrimaryRGBA()[2]), &(drawWindowPtr_->getSecondaryRGBA()[2]), drawWindowPtr_->isPrimaryActive());
	blueValueBox_->setBackgroundColour({ 50, 50, 255, 200 });
	alphaValueBox_ = std::make_shared<win::ColourValueTextbox>(gfx::Rectangle(), "alphaValueBox", renderer_, 18, 2, -3, &(drawWindowPtr_->getPrimaryRGBA()[3]), &(drawWindowPtr_->getSecondaryRGBA()[3]), drawWindowPtr_->isPrimaryActive());
	alphaValueBox_->setBackgroundColour({ 150,150,150,200 });
	
	colourValuesBox_->addChild(redValueBox_);
	colourValuesBox_->addChild(greenValueBox_);
	colourValuesBox_->addChild(blueValueBox_);
	colourValuesBox_->addChild(alphaValueBox_);
	addChild(colourValuesBox_);
}


inline void ColourPicker::initialiseColourSliders()
{
	redValueSlider_ = std::make_shared<win::ColourSlider>(renderer_, gfx::Rectangle(15, 660, 105, 20), "redValueSlider", gfx::Colour(255, 255, 255, 255), gfx::Colour(0, 0, 0, 255), &(drawWindowPtr_->getPrimaryRGBA()[0]), &(drawWindowPtr_->getSecondaryRGBA()[0]), drawWindowPtr_->isPrimaryActive());
	greenValueSlider_ = std::make_shared<win::ColourSlider>(renderer_, gfx::Rectangle(15, 660, 105, 20), "greenValueSlider", gfx::Colour(255, 255, 255, 255), gfx::Colour(0, 0, 0, 255), &(drawWindowPtr_->getPrimaryRGBA()[1]), &(drawWindowPtr_->getSecondaryRGBA()[1]), drawWindowPtr_->isPrimaryActive());
	blueValueSlider_ = std::make_shared<win::ColourSlider>(renderer_, gfx::Rectangle(15, 660, 105, 20), "blueValueSlider", gfx::Colour(255, 255, 255, 255), gfx::Colour(0, 0, 0, 255), &(drawWindowPtr_->getPrimaryRGBA()[2]), &(drawWindowPtr_->getSecondaryRGBA()[2]), drawWindowPtr_->isPrimaryActive());
	alphaValueSlider_ = std::make_shared<win::ColourSlider>(renderer_, gfx::Rectangle(15, 660, 105, 20), "alphaValueSlider", gfx::Colour(255, 255, 255, 255), gfx::Colour(0, 0, 0, 255), &(drawWindowPtr_->getPrimaryRGBA()[3]), &(drawWindowPtr_->getSecondaryRGBA()[3]), drawWindowPtr_->isPrimaryActive());

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

void ColourPicker::setActiveColourInDrawWindow() const
{
	assert(leftColourDisplay_->isActive() != rightColourDisplay_->isActive());
	if (leftColourDisplay_->isActive()) {
		if (!swappedDisplays_) {
			drawWindowPtr_->setIfPrimaryColourActive(true);
		}
		else{
			drawWindowPtr_->setIfPrimaryColourActive(false);
		}
	}
	else
	{
		if (!swappedDisplays_) {
			drawWindowPtr_->setIfPrimaryColourActive(false);
		}
		else {
			drawWindowPtr_->setIfPrimaryColourActive(true);
		}
	}
}

void ColourPicker::primaryActiveSwitchInBoxSlider() const
{
	redValueBox_->primaryActiveSwitch();
	greenValueBox_->primaryActiveSwitch();
	blueValueBox_->primaryActiveSwitch();
	alphaValueBox_->primaryActiveSwitch();

	redValueSlider_->primaryActiveSwitch();
	greenValueSlider_->primaryActiveSwitch();
	blueValueSlider_->primaryActiveSwitch();
	alphaValueSlider_->primaryActiveSwitch();
}

void ColourPicker::swapActiveColour() const
{
	leftColourDisplay_->swapIsActive();
	rightColourDisplay_->swapIsActive();

	primaryActiveSwitchInBoxSlider();

	setActiveColourInDrawWindow();
}

void ColourPicker::updateColourDisplaysFromDrawWindow() const
{
	const auto primaryRGBA = drawWindowPtr_->getPrimaryRGBA();
	const auto secondaryRGBA = drawWindowPtr_->getSecondaryRGBA();
	if (!swappedDisplays_) {
		leftColourDisplay_->setColour(gfx::Colour(primaryRGBA[0], primaryRGBA[1], primaryRGBA[2], primaryRGBA[3]));
		rightColourDisplay_->setColour(gfx::Colour(secondaryRGBA[0], secondaryRGBA[1], secondaryRGBA[2], secondaryRGBA[3]));
	}
	else {
		leftColourDisplay_->setColour(gfx::Colour(secondaryRGBA[0], secondaryRGBA[1], secondaryRGBA[2], secondaryRGBA[3]));
		rightColourDisplay_->setColour(gfx::Colour(primaryRGBA[0], primaryRGBA[1], primaryRGBA[2], primaryRGBA[3]));
	}
}

void ColourPicker::updateColourDisplays() const
{
	updateColourDisplaysFromDrawWindow();
	leftColourDisplay_->draw();
	rightColourDisplay_->draw();
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
	drawWindowPtr_->updateDrawToolRGBA();
	updateColourDisplays();
	updateColourValueBoxes();
	updateColourSliders();
}

void ColourPicker::updateAndRerender()
{
	update();
	
	draw();
	renderer_->renderPresent();
}

void ColourPicker::draw()
{	
	renderer_->renderBox(getRect(), getBackgroundColour());

	updateColourDisplaysFromDrawWindow();
	
	 for (auto const& child : getChildren())
	{
		child->draw();
	}
}