#pragma once
#include "PAINT_Tool.h"

class Shape;

namespace paint
{
	class ShapeTool :
		public Tool
	{
	private:
		Shape * activeShape_;
	public:
		ShapeTool();

		virtual ~ShapeTool();
	};
}
