#pragma once

namespace win
{
	class UIelement;
}

namespace paint
{
	class DrawWindow;

	namespace utils
	{
		 DrawWindow * findDrawWindow(win::UIelement * control);
	}
}
