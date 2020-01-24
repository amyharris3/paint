#pragma once
#include "PAINT_Shape.h"

namespace paint
{
	class Triangle :
		public Shape
	{
	public:
		Triangle();
		virtual ~Triangle();
		Triangle(const Triangle& that) = default;
		Triangle(Triangle && that) = default;
		Triangle& operator=(const Triangle & that) = default;
		Triangle& operator=(Triangle && that) = default;
	};
}
