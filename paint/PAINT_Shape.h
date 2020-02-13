#pragma once

namespace gfx
{
	struct Coords;
	class Line;
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

		virtual std::vector<gfx::Line> getGeometry(gfx::Coords startCoords, gfx::Coords currentCoords) = 0;

	};
}

