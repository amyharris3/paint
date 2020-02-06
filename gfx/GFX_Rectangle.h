#pragma once

namespace gfx
{
	class Rectangle
	{
	public:
		// Lifecycle.
		Rectangle();
		~Rectangle() = default;
		Rectangle(int rx, int ry, int w, int h);
		Rectangle(Rectangle const&) = default;
		Rectangle& operator=(Rectangle const&) = default;
		Rectangle(Rectangle &&) = default;
		Rectangle& operator=(Rectangle &&) = default;

		// API.
		bool containsPoint(int px, int py) const;
		
		int x;
		int y;
		int width;
		int height;
	};
}
