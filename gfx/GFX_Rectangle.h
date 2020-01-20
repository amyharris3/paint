#pragma once

namespace gfx
{
	class Rectangle
	{
	public:
		Rectangle()
		: Rectangle(0, 0, 1, 1)
		{

		}
		
		Rectangle(const int rx, const int ry, const int w, const int h)
		: x(rx)
		, y(ry)
		, width(w)
		, height(h)
		{
		}

		bool ContainsPoint(int x, int y) const;

		int x;
		int y;
		int width;
		int height;
	};
}
