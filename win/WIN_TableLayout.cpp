#include "WIN_TableLayout.h"
#include "GFX_Rectangle.h"
#include "WIN_UIelement.h"

#include <iostream>

using namespace win;

/*TableLayout::TableLayout(const int xmargin, const  int ymargin, const int xspacing, const int yspacing, const int elementHeight, const int elementWidth, int rows, int cols)
	: Layout(xmargin, ymargin, xspacing, yspacing, elementHeight, elementWidth)
	, rows_(rows)
	, cols_(cols)
{
}

TableLayout::~TableLayout()
{
}

void TableLayout::setRows(int rows)
{
	rows_ = rows;
}

void TableLayout::setCols(int cols)
{
	cols_ = cols;
}

//Given a set of children and a rectangle to fit them in, organises into rows and columns
void TableLayout::Apply(std::vector<std::shared_ptr<UIelement>> children, gfx::Rectangle rect)
{
	elementWidth_ = (int)round(((double)rect.width - ((double)xmargin_ * 2) - ((double)xspacing_ * ((double)cols_ - 1))) / (double)cols_);
	elementHeight_ = (int)round(((double)rect.height - ((double)ymargin_ * 2) - ((double)yspacing_ * ((double)rows_ - 1))) / (double)rows_);

	int xcount = 0;
	int ycount = 0;
	for (const auto& child : children) {
		LayoutSubElement element = { child, xmargin_ + (elementWidth_ * xcount), ymargin_ + (elementHeight_ * ycount) };

		xcount++;
		if (xcount == cols_) {
			xcount = 0;
			ycount++;
		}
	}

}*/

TableLayout::TableLayout(const int xmargin, const  int ymargin, const int xspacing, const int yspacing, int rows, int cols)
	: xmargin_(xmargin)
	, ymargin_(ymargin)
	, xspacing_(xspacing)
	, yspacing_(yspacing)
	, rows_(rows)
	, cols_(cols)
{
}

TableLayout::~TableLayout()
{
}

void TableLayout::setRows(int rows)
{
	rows_ = rows;
}

void TableLayout::setCols(int cols)
{
	cols_ = cols;
}

void TableLayout::Apply(std::vector<std::shared_ptr<UIelement>> const& elements, gfx::Rectangle const& bounds)
{
	int elementWidth = (int)round(((double)bounds.width - ((double)xmargin_ * 2) - ((double)xspacing_ * ((double)cols_ - 1))) / (double)cols_);
	int elementHeight = (int)round(((double)bounds.height - ((double)ymargin_ * 2) - ((double)yspacing_ * ((double)rows_ - 1))) / (double)rows_);

	int xcount = 0;
	int ycount = 0;
	for (const auto& elem : elements) {

		gfx::Rectangle rect(xmargin_ + ((elementWidth + xspacing_) * xcount), 
						ymargin_ + ((elementWidth + yspacing_) * ycount),
						elementWidth,
						elementHeight);
		elem->setRect(rect);

		xcount++;
		if (xcount == cols_) {
			xcount = 0;
			ycount++;
		}

	}
}