#include "PAINT_Utils.h"
#include "PAINT_Screen.h"
#include "PAINT_DrawWindow.h"
#include <cassert>

using namespace paint;
using namespace win;
using namespace utils;

DrawWindow * paint::utils::findDrawWindow(UIelement* control)
{
	/* Preconditions. */
	assert(control != nullptr && "null control in findDrawWindow()");

	/* Implementation */

	// Are we already at the DrawWindow?
	if (const auto dw = dynamic_cast<DrawWindow *>(control)) {
		return dw;
	}

	// Are we the screen?
	const auto parent = control->getParent();
	if (!parent) {
		const auto screen = dynamic_cast<Screen*>(control);
		return screen->getDrawWindow();
	}
	return findDrawWindow(parent);
}

ToolWindow* paint::utils::findToolWindow(UIelement* control)
{
	/* Preconditions. */
	assert(control != nullptr && "null control in findToolWindow()");

	/* Implementation */

	// Are we already at the DrawWindow?
	if (const auto tw = dynamic_cast<ToolWindow*>(control)) {
		return tw;
	}

	// Are we the screen?
	const auto parent = control->getParent();
	if (!parent) {
		const auto screen = dynamic_cast<Screen*>(control);
		return screen->getToolWindow();
	}
	return findToolWindow(parent);
}
