#pragma once
#include <vector>

namespace gfx {
	struct Coords;
	class Rectangle;
}

namespace gfx
{


	namespace utils
	{
		int findOutcode(gfx::Rectangle rect, int x, int y);

		std::vector<gfx::Coords> clippingHandler(Rectangle rect, Coords pStart, Coords pEnd);

		
	}
}
