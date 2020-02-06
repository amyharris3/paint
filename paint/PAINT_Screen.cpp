#include "PAINT_pch.h"
#include "PAINT_Screen.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_StatusBarWindow.h"
#include "WIN_Button.h"
#include "PAINT_ButtonFunctions.h"
#include "WIN_TableLayout.h"
#include "PAINT_MenuWindow.h"
#include "WIN_GenericBox.h"
#include "PAINT_ColourPicker.h"
#include "WIN_ButtonGroup.h"
#include "WIN_ToggleButton.h"

using namespace paint;
using namespace win;
using namespace gfx;

Screen::Screen(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name)
: Container(std::make_shared<FreeLayout>(), rect, name)
{
	// Creating drawWindow
	gfx::Rectangle drawRect(200, 40, 1000, 720);
	auto drawWindow = std::make_shared<DrawWindow>(renderer, drawRect, "drawWindow");
	drawWindow->setPrimaryColour(gfx::Colour(255, 0, 0, 255));
	drawWindow->setSecondaryColour(gfx::Colour(0, 255, 0, 255));
	
	this->addChild(drawWindow);
	drawWindow_ = drawWindow;

	// Creating toolWindow
	gfx::Rectangle toolRect(0, 40, 200, 720);
	auto toolWindow = std::make_shared<ToolWindow>(renderer, toolRect, "toolWindow");
	gfx::Colour toolColour{ 59, 156, 141, 120 };
	toolWindow->setBackgroundColour(toolColour);
	this->addChild(toolWindow);
	toolWindow_ = toolWindow;

	// Create toolbar inside tool window, allocating 3x2 table for 6 tool elements
	gfx::Rectangle toolbarRect(10, 50, 180, 260);
	auto toolbarLayout = std::make_shared<win::TableLayout>(20, 20, 20, 20, 3, 2);
	auto toolbox = std::make_shared<Window>(renderer,toolbarRect, "toolbarBox", toolbarLayout);
	const gfx::Colour toolboxColour{ 150, 255, 240, 255 };
	toolbox->setBackgroundColour(toolboxColour);
	// Create tool window buttons.
	gfx::Colour yellow(255, 255, 0, 255);
	for (int i = 0; i < 6; i++) {
		gfx::Rectangle buttonRect(20, 60, 60, 60);
		if (i == 0) {
			auto button = std::make_shared<ToggleButton>(renderer, buttonRect, "drawButton", "button_toggle_draw.png", toggleDraw);
			toolbox->addChild(button);
		}
		else if (i == 5){
			auto button = std::make_shared<Button>(renderer, buttonRect, "clearButton", "button_clear_screen.png", paint::clearScreen);
			toolbox->addChild(button);
		}
		else {
			auto button = std::make_shared<GenericBox>(buttonRect, "genericBox", yellow, yellow, renderer);
			toolbox->addChild(button);
		}
	}
	toolWindow->addChild(toolbox);
	toolWindow->setToolbox(toolbox);
	
	// Create thickness window inside tool window, allocating 3x1 table for 3 thickness choices
	gfx::Rectangle thicknessRect(10, 320, 180, 70);
	auto thicknessLayout = std::make_shared<win::TableLayout>(20, 20, 20, 20, 1, 3);
	auto thicknessBox = std::make_shared<ToolWindow>(renderer, thicknessRect, "thicknessBox", thicknessLayout);
	const gfx::Colour thicknessColour{ 150, 255, 240, 255 };
	thicknessBox->setBackgroundColour(thicknessColour);
	
	// Create button group for thickness buttons.
	auto thicknessButtonGroup = std::make_shared<ButtonGroup>();
	
	// Create thickness buttons.
	gfx::Rectangle buttonRect(20, 60, 60, 60);
	auto buttonThick1 = std::make_shared<ToggleButton>(renderer, buttonRect, "thickness1Button", "button_thickness1.png", setBrushThickness0);
	thicknessBox->addChild(buttonThick1);
	buttonThick1->setButtonGroup(thicknessButtonGroup);
	thicknessButtonGroup->addButtonChild(buttonThick1);
	
	auto buttonThick2 = std::make_shared<ToggleButton>(renderer, buttonRect, "thickness2Button", "button_thickness2.png", setBrushThickness1);
	thicknessBox->addChild(buttonThick2);
	buttonThick2->setButtonGroup(thicknessButtonGroup);
	thicknessButtonGroup->addButtonChild(buttonThick2);
	
	auto buttonThick3 = std::make_shared<ToggleButton>(renderer, buttonRect, "thickness3Button", "button_thickness3.png", setBrushThickness2);
	thicknessBox->addChild(buttonThick3);
	buttonThick3->setButtonGroup(thicknessButtonGroup);
	thicknessButtonGroup->addButtonChild(buttonThick3);

	toolWindow->addChild(thicknessBox);

	// Create area for colour picker
	gfx::Rectangle colourPickerRect(10, 400, 180, 220);
	auto colourPicker = std::make_shared<ColourPicker>(colourPickerRect, renderer, drawWindow);
	const gfx::Colour colourPickerColour{ 150, 255, 240, 255 };
	colourPicker->setBackgroundColour(colourPickerColour);
	//colourPicker->updateColourValueBoxes();
	toolWindow->addChild(colourPicker);
	toolWindow->setColourPicker(colourPicker);
	
	// Creating statusWindow
	gfx::Rectangle statusRect(0, 760, 1200, 40);
	auto statusWindow = std::make_shared<StatusBarWindow>(renderer, statusRect, "statusWindow", 200, 40);
	gfx::Colour statusColour{ 40, 115, 103, 255 };
	statusWindow->setBackgroundColour(statusColour);
	this->addChild(statusWindow);

	// Creating menuWindow
	gfx::Rectangle menuRect(0, 0, 1200, 40);
	auto menuWindow = std::make_shared<MenuWindow>(renderer, menuRect, "menuWindow");
	gfx::Colour menuColour{113, 114, 117, 255 };
	menuWindow->setBackgroundColour(menuColour);
	this->addChild(menuWindow);
	
}

void Screen::updateAndRerender()
{
	for (const auto& child : getChildren()) {
		child->updateAndRerender();
	}
}

