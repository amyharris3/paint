#include "WIN_TableLayout.h"
#include "GFX_Rectangle.h"
#include "WIN_UIelement.h"

#include <iostream>

using namespace win;

TableLayout::TableLayout(const int xmargin, const int ymargin, const int xspacing, const int yspacing, int rows, int cols)
	: xmargin_(xmargin)
	, ymargin_(ymargin)
	, xspacing_(xspacing)
	, yspacing_(yspacing)
	, rows_(rows)
	, cols_(cols)
{
}


void TableLayout::setRows(const int rows)
{
	rows_ = rows;
}

void TableLayout::setCols(const int cols)
{
	cols_ = cols;
}

void TableLayout::Apply(std::vector<std::shared_ptr<UIelement>> const& elements, gfx::Rectangle const& bounds)
{
	const auto elementWidth = int(round(
		(double(bounds.width) - (double(xmargin_) * 2) - (double(xspacing_) * (double(cols_) - 1))) / double(cols_)));
	const auto elementHeight = int(round(
		(double(bounds.height) - (double(ymargin_) * 2) - (double(yspacing_) * (double(rows_) - 1))) / double(rows_)));

	int xcount = 0;
	int ycount = 0;
	for (const auto& elem : elements) {

		gfx::Rectangle rect(bounds.x + xmargin_ + ((elementWidth + xspacing_) * xcount), 
						bounds.y + ymargin_ + ((elementHeight + yspacing_) * ycount),
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