#include "PAINT_ButtonFunctions.h"
#include "WIN_Button.h"
#include <iostream>
#include "PAINT_Utils.h"
#include "PAINT_DrawWindow.h"

using namespace win;
using namespace paint;

void paint::myAction(Button*)
{
	std::cout << "Im doing an action yay! \n";
}

void paint::toggleDraw(Button* button)
{
	auto dw = utils::findDrawWindow(button);
	dw->toggleDraw();
}

void paint::swapColours(Button* button)
{
	auto dw = utils::findDrawWindow(button);
	dw->swapPrimarySecondaryColours();
	auto cpick = utils::findToolWindow(button)->getColourPicker();
	cpick->swappedDisplaysSwitch();
	cpick->updateColourDisplaysFromDrawWindow();
	cpick->setActiveColourInDrawWindow();
	cpick->leftActiveSwitchInBoxSlider();
	//cpick->updateAndRerender();
	cpick->update();
}

void paint::clearScreen(Button* button)
{
	const auto dw = utils::findDrawWindow(button);
	dw->clearScreen();
}

