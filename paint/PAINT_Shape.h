#pragma once

#include "PAINT_DrawFlags.h"

namespace paint
{
	class DrawFlags;
	
	class Shape
	{
	private:
		DrawFlags * drawFlag_;
		
	public:
		Shape() = default;
		virtual ~Shape() = default;
		Shape(const Shape& that) = default;
		Shape(Shape && that) = default;
		Shape& operator=(const Shape & that) = default;
		Shape& operator=(Shape && that) = default;
	};
}
