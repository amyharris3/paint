#include "PAINT_Screen.h"
#include <SDL.h>
#include <memory>
#include "PAINT_DrawWindow.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_StatusBarWindow.h"
#include "WIN_Button.h"
#include "PAINT_ButtonFunctions.h"
#include "WIN_TableLayout.h"
#include "PAINT_MenuWindow.h"
#include "WIN_GenericBox.h"
#include "PAINT_ColourPicker.h"

using namespace paint;
using namespace win;
using namespace gfx;

Screen::Screen(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name)
: Container(std::make_shared<FreeLayout>(), rect, name)
{
	// Creating drawWindow
	gfx::Rectangle drawRect(200, 40, 1000, 720);
	auto drawWindow = std::make_shared<DrawWindow>(renderer, drawRect, "drawWindow");
	//gfx::Colour drawColour{ 255, 255, 255, 255 };
	//drawWindow->setBackgroundColour(drawColour);
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

	// Creating tool window buttons
	//gfx::Rectangle drawButtonRect(20, 60, 60, 60);
	//auto drawButton = std::make_shared<Button>(renderer, drawButtonRect, "drawButton", "button_toggle_draw.png", toggleDraw);
	//toolWindow->addChild(drawButton);

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
			auto button = std::make_shared<Button>(renderer, buttonRect, "drawButton", "button_toggle_draw.png", toggleDraw);
			toolbox->addChild(button);
		}
		else if (i == 5){
			auto button = std::make_shared<Button>(renderer, buttonRect, "clearButton", "button_clear_screen.png", clearScreen);
			toolbox->addChild(button);
		}
		else {
			auto button = std::make_shared<GenericBox>(buttonRect, "genericBox", yellow, yellow, renderer);
			toolbox->addChild(button);
		}
	}
	toolWindow->addChild(toolbox);
	toolWindow->setToolbox(toolbox);

	// Rectangle reserved for brush thickness
	auto brushOptionsBox = std::make_shared<Window>(renderer, gfx::Rectangle(10, 320, 180, 40), "toolbarBox", toolbarLayout);
	brushOptionsBox->setBackgroundColour(gfx::Colour(150, 255, 240, 255));
	toolWindow->addChild(brushOptionsBox);
	
	// Create area for colour picker
	gfx::Rectangle colourPickerRect(10, 370, 180, 220);
	auto colourPicker = std::make_shared<ColourPicker>(colourPickerRect, renderer, drawWindow);
	const gfx::Colour colourPickerColour{ 150, 255, 240, 255 };
	colourPicker->setBackgroundColour(colourPickerColour);
	colourPicker->updateColourValueBoxes();
	toolWindow->addChild(colourPicker);
	toolWindow->setColourPicker(colourPicker);
	
	// Creating statusWindow
	gfx::Rectangle statusRect(0, 760, 1200, 40);
	auto statusWindow = std::make_shared<StatusBarWindow>(renderer, statusRect, "statusWindow");
	gfx::Colour statusColour{ 40, 115, 103, 255 };
	statusWindow->setBackgroundColour(statusColour);
	this->addChild(statusWindow);
	statusWindow_ = statusWindow;

	// Creating menuWindow
	gfx::Rectangle menuRect(0, 0, 1200, 40);
	auto menuWindow = std::make_shared<MenuWindow>(renderer, menuRect, "menuWindow");
	gfx::Colour menuColour{113, 114, 117, 255 };
	menuWindow->setBackgroundColour(menuColour);
	this->addChild(menuWindow);
	menuWindow_ = menuWindow;

}

void Screen::updateAndRerender()
{
	for (const auto& child : getChildren()) {
		child->updateAndRerender();
	}
}


//void Screen::setDrawWindow(DrawWindow* drawWindow)
//{
//	drawWindow_ = drawWindow;
//}
//
//void Screen::setToolWindow(ToolWindow* toolWindow)
//{
//	toolWindow_ = toolWindow;
//}

//DrawWindow* Screen::getDrawWindow()
//{
//
//}
//
//ToolWindow* Screen::getToolWindow()
//{
//
//}