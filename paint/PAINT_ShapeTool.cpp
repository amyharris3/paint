#include "PAINT_pch.h"
#include "PAINT_ShapeTool.h"

using namespace paint;

ShapeTool::ShapeTool()
	: activeShape_(nullptr)
{
	
}

void ShapeTool::setActiveShape(Shape* shape)
{
	activeShape_ = shape;
}

