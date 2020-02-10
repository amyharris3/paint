#pragma once
#include "PAINT_Shape.h"
#include "GFX_Line.h"

namespace paint
{
	class Rectangle final :
		public Shape
	{
	public:
		Rectangle() = default;
		virtual ~Rectangle() = default;
		Rectangle(const Rectangle& that) = default;
		Rectangle(Rectangle && that) = default;
		Rectangle& operator=(const Rectangle & that) = default;
		Rectangle& operator=(Rectangle && that) = default;

		std::vector<gfx::Line> shapeGeometry(win::Coords startCoords, win::Coords currentCoords) override;
	};
}
