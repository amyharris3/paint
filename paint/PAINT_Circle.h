#pragma once
#include "PAINT_Shape.h"

namespace paint
{
	class Circle final :
		public Shape
	{
	public:
		Circle() = default;
		virtual ~Circle() = default;
		Circle(const Circle& that) = default;
		Circle(Circle&& that) = default;
		Circle& operator=(const Circle& that) = default;
		Circle& operator=(Circle&& that) = default;

		std::vector<gfx::Line> shapeGeometry(win::Coords startCoords, win::Coords currentCoords) override;
		std::vector<int> ellipse(int x, int a, int b, int h, int k) const;

	};
}
