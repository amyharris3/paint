#include "PAINT_pch.h"
#include "PAINT_Tool.h"
#include "PAINT_Brush.h"

using namespace paint;

Tool::Tool()
	: lines_(NULL)
	, activeBrush_(nullptr)
{
}


void Tool::setActiveBrush(std::shared_ptr<Brush> brush)
{
	activeBrush_ = std::move(brush);
}


void Tool::clearLines()
{
	lines_.clear();
}





