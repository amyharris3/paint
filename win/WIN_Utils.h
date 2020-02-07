#pragma once

namespace gfx {
	class Rectangle;
}

namespace win
{
	namespace utils
	{
		bool filterNumerical(const char c);

		int findOutcode(gfx::Rectangle rect, int x, int y);
		
	}
}
