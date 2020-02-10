#pragma once


namespace win {
	struct Coords;
}

namespace gfx
{
	struct Line;
}

namespace paint
{
	//class DrawFlags;
	
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape() = default;
		Shape(const Shape& that) = default;
		Shape(Shape && that) = default;
		Shape& operator=(const Shape & that) = default;
		Shape& operator=(Shape && that) = default;

		virtual std::vector<gfx::Line> shapeGeometry(win::Coords startCoords, win::Coords currentCoords) = 0;

	};
}
