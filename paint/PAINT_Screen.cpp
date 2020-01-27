#include "PAINT_Screen.h"
#include <SDL.h>
#include "PAINT_DrawWindow.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_StatusBarWindow.h"
#include "WIN_Button.h"
#include "PAINT_ButtonFunctions.h"
#include <memory>
#include "WIN_Layout.h"
#include "PAINT_MenuWindow.h"


using namespace paint;
using namespace win;
using namespace gfx;

Screen::Screen(SDL_Renderer* renderer, std::shared_ptr<Layout> layout, const gfx::Rectangle& rect, const char* name)
	: Container(layout, rect, name)
{
	// Creating drawWindow
	gfx::Rectangle drawRect(200, 40, 1000, 720);
	auto drawWindow = std::make_shared<DrawWindow>(renderer, drawRect, "drawWindow");
	gfx::Colour drawColour{ 255, 255, 255, 255 };
	drawWindow->setBackgroundColour(drawColour);
	this->AddChild(drawWindow);
	drawWindow_ = drawWindow;

	// Creating toolWindow
	gfx::Rectangle toolRect(0, 40, 200, 720);
	auto toolWindow = std::make_shared<ToolWindow>(renderer, toolRect, "toolWindow");
	gfx::Colour toolColour{ 59, 156, 141, 120 };
	toolWindow->setBackgroundColour(toolColour);
	this->AddChild(toolWindow);
	toolWindow_ = toolWindow;

	// Creating tool window buttons
	gfx::Rectangle drawButtonRect(20, 60, 60, 60);
	auto drawButton = std::make_shared<Button>(renderer, drawButtonRect, "drawButton", "button_toggle_draw.png", toggleDraw);
	//screen_.AddChild(drawButton);
	toolWindow->AddChild(drawButton);

	// Creating statusWindow
	gfx::Rectangle statusRect(0, 760, 1200, 40);
	auto statusWindow = std::make_shared<StatusBarWindow>(renderer, statusRect, "statusWindow");
	gfx::Colour statusColour{ 40, 115, 103, 255 };
	statusWindow->setBackgroundColour(statusColour);
	this->AddChild(statusWindow);
	statusWindow_ = statusWindow;

	// Creating menuWindow
	gfx::Rectangle menuRect(0, 0, 1200, 40);
	auto menuWindow = std::make_shared<MenuWindow>(renderer, menuRect, "menuWindow");
	gfx::Colour menuColour{113, 114, 117, 255 };
	menuWindow->setBackgroundColour(menuColour);
	this->AddChild(menuWindow);
	menuWindow_ = menuWindow;

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