#pragma once

#include "PAINT_DrawFlags.h"

class DrawFlags;

namespace paint
{
	class Shape
	{
	private:
		DrawFlags * drawFlag_;
	public:
		Shape();
		virtual ~Shape();
	};
}
