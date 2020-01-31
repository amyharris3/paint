#include "PAINT_ButtonFunctions.h"
#include "WIN_Button.h"
#include <iostream>
#include "PAINT_Utils.h"
#include "PAINT_DrawWindow.h"

using namespace win;
using namespace paint;

//void myAction(win::Button* button)
//{
//	std::cout << "Im doing an action yay! \n";
//}
//
//void paint::foo()
//{
//	Button b;
//	b.action = myAction;
//}

void paint::myAction(win::Button* button)
{
	std::cout << "Im doing an action yay! \n";
}

void paint::toggleDraw(win::Button* button)
{
	auto dw = utils::findDrawWindow(button);
	dw->toggleDraw();
}

void paint::swapColours(win::Button* button)
{
	auto dw = utils::findDrawWindow(button);
	dw->swapColours();
	auto cpick = paint::utils::findToolWindow(button)->getColourPicker();
	cpick->swapDisplaysSwitch();
	cpick->updateColourDisplaysFromDrawWindow();
	cpick->setDrawColourFromActive();
	cpick->updateColourValueBoxes();
	cpick->updateColourSliders();
}

void paint::clearScreen(win::Button* button)
{
	auto dw = utils::findDrawWindow(button);
	dw->clearScreen();
}

