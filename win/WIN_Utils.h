#pragma once

namespace gfx {
	class Rectangle;
}

namespace win
{
	namespace utils
	{
		void getMouseState(int& xMouse, int& yMouse, bool dummyValues = false, int dummyX = 0, int dummyY = 0);

		bool filterNumerical(char c);

	}
}
