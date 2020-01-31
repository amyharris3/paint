#pragma once
#include "PAINT_Tool.h"
#include "PAINT_Shape.h"

namespace paint
{
	class Shape;
	
	class ShapeTool :
		public Tool
	{
	public:
		ShapeTool();
		virtual ~ShapeTool() = default;
		ShapeTool(const ShapeTool& that) = default;
		ShapeTool(ShapeTool && that) = default;
		ShapeTool& operator=(const ShapeTool & that) = default;
		ShapeTool& operator=(ShapeTool && that) = default;
		
	private:
		std::shared_ptr<Shape> activeShape_;
	};
}
