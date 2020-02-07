#pragma once
#include "PAINT_ColourPicker.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_StatusBarWindow.h"

namespace win
{
	class UIelement;
}

namespace paint
{
	class DrawWindow;

	namespace utils
	{
		 DrawWindow* findDrawWindow(win::UIelement * control);
		 ToolWindow* findToolWindow(win::UIelement* control);
		 StatusBarWindow* findStatusBarWindow(win::UIelement* control);
	}
}
