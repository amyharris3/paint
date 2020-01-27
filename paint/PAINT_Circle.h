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

	};
}
