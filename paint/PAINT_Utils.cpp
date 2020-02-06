#include "PAINT_pch.h"
#include "PAINT_Utils.h"
#include "PAINT_Screen.h"
#include "PAINT_DrawWindow.h"

using namespace paint;
using namespace win;
using namespace utils;

DrawWindow * paint::utils::findDrawWindow(UIelement* control)
{
	/* Preconditions. */
	try
	{
		if (!control)
		{
			throw std::runtime_error("Null control in findDrawWindow().");
		}
	}
	catch(std::runtime_error &e)
	{
		std::cout << e.what() << '\n';
		throw;
	}

	/* Implementation */

	// Are we already at the DrawWindow?
	if (const auto dw = dynamic_cast<DrawWindow *>(control)) {
		return dw;
	}

	// Are we the screen?
	const auto parent = control->getParent();
	if (!parent) {
#if !defined(NDEBUG)
		const auto screen = dynamic_cast<Screen*>(control);
#else
		const auto screen = static_cast<Screen*>(control);
#endif
		assert(screen);
		return screen->getDrawWindow();
	}
	return findDrawWindow(parent);
}

