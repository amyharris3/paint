#pragma once
#include "PAINT_Shape.h"

namespace paint
{
	class Ellipse final :
		public Shape
	{
	public:
		Ellipse() = default;
		virtual ~Ellipse() = default;
		Ellipse(const Ellipse& that) = default;
		Ellipse(Ellipse&& that) = default;
		Ellipse& operator=(const Ellipse& that) = default;
		Ellipse& operator=(Ellipse&& that) = default;

		std::vector<gfx::Line> shapeGeometry(win::Coords startCoords, win::Coords currentCoords) override;
		std::vector<int> ellipse(int x, int a, int b, int h, int k) const;

	};
}
