#include "PAINT_Utils.h"
#include "WIN_Container.h"
#include "PAINT_Screen.h"
#include "PAINT_DrawWindow.h"
#include <cassert>
#include <iostream>

using namespace paint;
using namespace win;
using namespace utils;

DrawWindow * paint::utils::findDrawWindow(UIelement* control)
{
	/* Preconditions. */
	assert(control != nullptr && "null control in findDrawWindow()");

	/* Implementation */

	// Are we already at the DrawWindow?
	if (auto dw = dynamic_cast<DrawWindow *>(control)) {
		return dw;
	}

	// Are we the screen?
	auto parent = control->getParent();
	if (!parent) {
		auto screen = static_cast<Screen*>(control);
		return screen->getDrawWindow();
	}
	return findDrawWindow(parent);
}

