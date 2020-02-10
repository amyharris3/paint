#pragma once
#include "PAINT_Shape.h"

namespace paint
{
	class Triangle final : 
		public Shape
	{
	public:
		Triangle() = default;
		virtual ~Triangle() = default;
		Triangle(const Triangle& that) = default;
		Triangle(Triangle && that) = default;
		Triangle& operator=(const Triangle & that) = default;
		Triangle& operator=(Triangle && that) = default;

		std::vector<gfx::Line> shapeGeometry(win::Coords startCoords, win::Coords currentCoords) override;
	};
}
