#pragma once
#include "PAINT_Shape.h"

namespace paint
{
	class Rectangle final :
		public Shape
	{
	public:
		Rectangle() = default;
		virtual ~Rectangle();
		Rectangle(const Rectangle& that) = default;
		Rectangle(Rectangle && that) = default;
		Rectangle& operator=(const Rectangle & that) = default;
		Rectangle& operator=(Rectangle && that) = default;
	};
}
