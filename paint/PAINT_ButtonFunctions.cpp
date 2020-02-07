#include "PAINT_pch.h"
#include "PAINT_ButtonFunctions.h"
#include "PAINT_Utils.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_Brush.h"
#include "WIN_ToggleButton.h"
#include "WIN_ButtonStates.h"
#include "PAINT_StatusBarWindow.h"

using namespace win;
using namespace paint;

void paint::toggleDraw(UIelement* control)
{
#if !defined(NDEBUG)
	const auto button = dynamic_cast<ToggleButton*>(control);
#else
	const auto button = static_cast<ToggleButton*>(control);    // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
#endif
	auto dw = utils::findDrawWindow(button);
	assert(dw && "findDrawWindow in toggleDraw returned nullptr.");
	dw->toggleDrawTool(button);

	auto sw = utils::findStatusBarWindow(button);
	sw->outputMessage("Toggled draw");
}

static void paint::setBrushThickness(UIelement* control, int thick)
{
#if !defined(NDEBUG)
	const auto button = dynamic_cast<ToggleButton*>(control);
#else
	const auto button = static_cast<ToggleButton*>(control);    // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
#endif
	assert((thick == 0) || (thick == 1) || (thick == 2) && "Brush thickness set to value other than 0, 1, or 2 in ButtonFunctions.");
	const auto dw = utils::findDrawWindow(button);
	assert(dw && "findDrawWindow in setBrushThickness returned nullptr.");
	const auto activeTool = dw->getActiveTool();
	if (activeTool) {
		const auto activeBrush = activeTool->getActiveBrush();
		if (activeBrush) {
			if (button->getState() == ButtonStates::on) {
				activeBrush->setThickness(thick);
			}
			else {
				activeBrush->setThickness(0);
			}
		}
	}
	auto sw = utils::findStatusBarWindow(button);
	char message[30];
	sprintf_s(message, "Set brush thickness to %d", thick);
	sw->outputMessage(message);
}

void paint::setBrushThickness0(UIelement* control)
{
	setBrushThickness(control, 0);
}

void paint::setBrushThickness1(UIelement* control)
{
	setBrushThickness(control, 1);
}

void paint::setBrushThickness2(UIelement* control)
{
	setBrushThickness(control, 2);
}

void paint::swapColours(UIelement* control)
{
	auto cPick = utils::findToolWindow(control)->getColourPicker();
	cPick->swappedDisplaysSwitch();
	cPick->updateColourDisplaysFromDrawWindow();
	cPick->setActiveColourInDrawWindow();
	cPick->primaryActiveSwitchInBoxSlider();
	//cPick->updateAndRerender();
	cPick->update();

	auto sw = utils::findStatusBarWindow(control);
	sw->outputMessage("Toggled colour swap");
}

void paint::clearScreen(UIelement* control)
{
	const auto dw = utils::findDrawWindow(control);
	dw->clearWindow();
}

