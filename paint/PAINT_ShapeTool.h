#pragma once
#include "PAINT_Tool.h"
#include "PAINT_Shape.h"

namespace paint
{
	class Shape;
	
	class ShapeTool :
		public Tool
	{
	private:
		Shape * activeShape_;  // NOLINT(clang-diagnostic-unused-private-field)
	public:
		ShapeTool();
		virtual ~ShapeTool() = default;
		ShapeTool(const ShapeTool& that) = default;
		ShapeTool(ShapeTool && that) = default;
		ShapeTool& operator=(const ShapeTool & that) = default;
		ShapeTool& operator=(ShapeTool && that) = default;
	};
}
