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

		std::vector<gfx::Line> getGeometry(gfx::Coords startCoords, gfx::Coords currentCoords) override;

	};
}
