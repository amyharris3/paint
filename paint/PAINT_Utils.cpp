#include "PAINT_pch.h"
#include "PAINT_Utils.h"
#include "PAINT_Screen.h"
#include "PAINT_DrawWindow.h"

using namespace paint;
using namespace win;
using namespace utils;

DrawWindow* paint::utils::findDrawWindow(UIelement* control)
{
	/* Preconditions. */
	try {
		if (!control) {
			throw std::runtime_error("Null control in findDrawWindow().");
		}
	}
	catch (std::runtime_error & e) {
		std::cout << e.what() << '\n';
		throw;
	}

	/* Implementation */

	// Are we already at the DrawWindow?
	if (const auto dw = dynamic_cast<DrawWindow*>(control)) {
		return dw;
	}

	// Are we the screen?
	const auto parent = control->getParent();
	if (!parent) {
#if !defined(NDEBUG)
		const auto screen = dynamic_cast<Screen*>(control);
#else
		const auto screen = static_cast<Screen*>(control);  // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
#endif
		assert(screen);
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

StatusBarWindow* paint::utils::findStatusBarWindow(UIelement* control)
{
	/* Preconditions. */
	assert(control != nullptr && "null control in findToolWindow()");

	/* Implementation */

	// Are we already at the DrawWindow?
	if (const auto sw = dynamic_cast<StatusBarWindow*>(control)) {
		return sw;
	}

	// Are we the screen?
	const auto parent = control->getParent();
	if (!parent) {
		const auto screen = dynamic_cast<Screen*>(control);
		return screen->getStatusBarWindow();
	}
	return findStatusBarWindow(parent);
}
