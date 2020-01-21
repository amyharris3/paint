#include "WIN_Layout.h"

using namespace win;

/*Layout::Layout()
	: xmargin_(0)
	, ymargin_(0)
	, xspacing_(0)
	, yspacing_(0)
	, childHeight_(1)
	, childWidth_(1)
{
}*/

Layout::Layout(const int xmargin, const  int ymargin, const int xspacing, const int yspacing, const int childHeight, const int childWidth)
	: xmargin_(xmargin)
	, ymargin_(ymargin)
	, xspacing_(xspacing)
	, yspacing_(yspacing)
	, childHeight_(childHeight)
	, childWidth_(childWidth)
{

}

Layout::~Layout()
{
}

void Layout::setXMargin(int xmargin)
{
	xmargin_ = xmargin;
}

void Layout::setYMargin(int ymargin)
{
	ymargin_ = ymargin;
}

void Layout::setXSpacing(int xspacing)
{
	xspacing_ = xspacing;
}

void Layout::setYSpacing(int yspacing)
{
	yspacing_ = yspacing;
}

void Layout::Apply(std::vector<std::shared_ptr<UIelement>> children, gfx::Rectangle rect)
{

}