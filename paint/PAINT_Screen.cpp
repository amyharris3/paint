#include "PAINT_pch.h"
#include "PAINT_Screen.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_StatusBarWindow.h"
#include "PAINT_ButtonFunctions.h"
#include "WIN_TableLayout.h"
#include "PAINT_MenuWindow.h"
#include "WIN_GenericBox.h"
#include "PAINT_ColourPicker.h"
#include "WIN_ButtonGroup.h"
#include "WIN_ToggleButton.h"
#include "WIN_DisabledUIelementGroup.h"

using namespace paint;
using namespace win;
using namespace gfx;

static ButtonInfo toolbox_button_info[] = {
	{ "drawButton", "button_toggle_draw.png", toggleDraw  },
	{"rectangleButton", "button_draw_rectangle.png", toggleDrawRectangle  },
	{ "ellipseButton", "button_draw_ellipse.png", toggleDrawEllipse  },
	{ "triangleButton", "button_draw_triangle.png", toggleDrawTriangle  },
	//{ "lockButton", "button_lock.png", toggleLock}
	//{ "clearButton", "button_clear_screen.png", clearScreen, false }
};

static constexpr auto numToolBoxButtons = sizeof(toolbox_button_info) / sizeof(ButtonInfo);

static ButtonInfo thickness_button_info[] = {
	{ "thickness1Button", "button_thickness1.png", setBrushThickness0 },
	{ "thickness2Button", "button_thickness2.png", setBrushThickness1 },
	{ "thickness3Button", "button_thickness3.png", setBrushThickness2 },
};

static constexpr auto numThicknessButtons = sizeof(thickness_button_info) / sizeof(ButtonInfo);


static void makeButtons(win::SDLRenderer* renderer, Rectangle& rect, ButtonInfo* buttonInfo, int const numButtons, Window* window, std::shared_ptr<ButtonGroup> const & buttonGroup = nullptr, std::shared_ptr<DisabledUIelementGroup> const & disableGroup = nullptr)
{
	for (auto i = 0; i < numButtons; ++i) {
		auto button = std::make_shared<ToggleButton>(renderer, rect, buttonInfo[i].buttonName, buttonInfo[i].buttonSpritePath, buttonInfo[i].action);
		window->addChild(button);
		if (buttonGroup) {
			button->setButtonGroup(buttonGroup);
			buttonGroup->addButtonChild(button);
		}
		if (disableGroup) {
			button->setDisableGroup(disableGroup);
			//disableGroup->addButtonChild(button);
		}
	}
}

Screen::Screen(win::SDLRenderer* renderer, const gfx::Rectangle& rect, const char* name)
: Container(std::make_shared<FreeLayout>(), rect, name)
{
	// Creating drawWindow
	gfx::Rectangle drawRect(200, 40, 1000, 720);
	auto drawWindow = std::make_shared<DrawWindow>(renderer, drawRect, "drawWindow");
	drawWindow->setPrimaryColour(gfx::Colour(255, 0, 0, 255));
	drawWindow->setSecondaryColour(gfx::Colour(0, 255, 0, 255));
	drawWindow->updateAllToolsRGBA();
	
	this->addChild(drawWindow);
	drawWindow_ = drawWindow;

	// Creating toolWindow
	gfx::Rectangle toolRect(0, 40, 200, 720);
	auto toolWindow = std::make_shared<ToolWindow>(toolRect, "toolWindow");
	gfx::Colour toolColour{ 59, 156, 141, 120 };
	toolWindow->setBackgroundColour(toolColour);
	this->addChild(toolWindow);
	toolWindow_ = toolWindow;

	// Create toolbar inside tool window, allocating 3x2 table for 6 tool elements
	gfx::Rectangle toolbarRect(10, 50, 180, 260);
	auto toolbarLayout = std::make_shared<win::TableLayout>(20, 20, 20, 20, 3, 2);
	auto toolbox = std::make_shared<Window>(toolbarRect, "toolbarBox", toolbarLayout);
	const gfx::Colour toolboxColour{ 150, 255, 240, 255 };
	toolbox->setBackgroundColour(toolboxColour);
	
	// Create tool window buttons.
	auto toolboxButtonGroup = std::make_shared<ButtonGroup>();
	gfx::Rectangle buttonRect(20, 60, 60, 60);
	makeButtons(renderer, buttonRect, toolbox_button_info, numToolBoxButtons, toolbox.get(), toolboxButtonGroup);

	// Make clear screen button.
	auto button = std::make_shared<Button>(renderer, rect, "clearScreenButton", "button_clear_screen.png", clearScreen);
	toolbox->addChild(button);



	// Make lock button.
	auto lockButton = std::make_shared<ToggleButton>(renderer, rect, "lockButton", "button_lock.png", toggleLock);
	// Make DisabledUIelementGroup for lock button.
	auto disabledLockGroup = std::make_shared<DisabledUIelementGroup>();
	for (auto const & child : toolbox->getChildren()) {
		disabledLockGroup->addChild(child);
	}
	lockButton->setDisableGroup(disabledLockGroup);
	toolbox->addChild(lockButton);

	toolWindow->addChild(toolbox);
	toolWindow->setToolbox(toolbox);
	
	// Create thickness window inside tool window, allocating 3x1 table for 3 thickness choices
	gfx::Rectangle thicknessRect(10, 320, 180, 70);
	auto thicknessLayout = std::make_shared<win::TableLayout>(20, 20, 20, 20, 1, 3);
	auto thicknessBox = std::make_shared<ToolWindow>(thicknessRect, "thicknessBox", thicknessLayout);
	const gfx::Colour thicknessColour{ 150, 255, 240, 255 };
	thicknessBox->setBackgroundColour(thicknessColour);
	
	// Create button group for thickness buttons.
	auto thicknessButtonGroup = std::make_shared<ButtonGroup>();
	
	// Create thickness buttons.
	makeButtons(renderer, buttonRect, thickness_button_info, numThicknessButtons, thicknessBox.get(), thicknessButtonGroup);
	thicknessBox->getChildren()[0]->setActivated(true);

	toolWindow->setThicknessButtonGroup(thicknessButtonGroup);
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
	auto statusWindow = std::make_shared<StatusBarWindow>(statusRect, "statusWindow", 200, 40);
	gfx::Colour statusColour{ 40, 115, 103, 255 };
	statusWindow->setBackgroundColour(statusColour);
	this->addChild(statusWindow);
	statusBarWindow_ = statusWindow;

	// Creating menuWindow
	gfx::Rectangle menuRect(0, 0, 1200, 40);
	auto menuWindow = std::make_shared<MenuWindow>(menuRect, "menuWindow");
	gfx::Colour menuColour{113, 114, 117, 255 };
	menuWindow->setBackgroundColour(menuColour);
	this->addChild(menuWindow);
	
}

void Screen::updateAndRerender(win::SDLRenderer* renderer)
{
	for (const auto& child : getChildren()) {
		child->updateAndRerender(renderer);
	}
}

