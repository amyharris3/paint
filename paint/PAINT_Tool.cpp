#include "PAINT_Tool.h"
#include "PAINT_Brush.h"

using namespace paint;


Tool::Tool()
	: lines_(NULL)
{
}


void Tool::setActiveBrush(std::shared_ptr<Brush> brush)
{
	activeBrush_ = brush;
}


void Tool::clearLines()
{
	lines_.clear();
}



