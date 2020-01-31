#include "PAINT_ButtonFunctions.h"
#include "WIN_Button.h"
#include <iostream>
#include "PAINT_Utils.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_Brush.h"
#include "WIN_ToggleButton.h"

using namespace win;
using namespace paint;

void paint::myAction(win::Button* button)
{
	std::cout << "Im doing an action yay! \n";
}

void paint::toggleDraw(win::ToggleButton* button)
{
	auto dw = utils::findDrawWindow(button);
	dw->toggleDrawTool(button);
}

void paint::setBrushThickness0(win::ToggleButton* button)
{
	auto dw = utils::findDrawWindow(button);
	const auto activetool = dw->getActiveTool();
	if (activetool)
	{
		const auto activebrush = activetool->getActiveBrush();
		if (activebrush) {
			activebrush->setThickness(0);
		}
	}
}

void paint::setBrushThickness1(win::ToggleButton* button)
{
	auto dw = utils::findDrawWindow(button);
	const auto activetool = dw->getActiveTool();
	if (activetool)
	{
		const auto activebrush = activetool->getActiveBrush();
		if (activebrush) {
			if (button->getState() == ToggleButton::on) {
				activebrush->setThickness(1);
			}
			else {
				activebrush->setThickness(0);
			}
		}
	}
}

void paint::setBrushThickness2(win::ToggleButton* button)
{
	auto dw = utils::findDrawWindow(button);
	const auto activetool = dw->getActiveTool();
	if (activetool)
	{
		const auto activebrush = activetool->getActiveBrush();
		if (activebrush)
		{
			if (button->getState() == ToggleButton::on) {
				activebrush->setThickness(2);
			}
			else {
				activebrush->setThickness(0);
			}
		}
	}
}
