#include "WIN_TableLayout.h"
#include "GFX_Rectangle.h"
#include "WIN_UIelement.h"

using namespace win;

TableLayout::TableLayout(const int xMargin, const  int yMargin, const int xSpacing, const int ySpacing, const int rows, const int cols)
	: xMargin_(xMargin)
	, yMargin_(yMargin)
	, xSpacing_(xSpacing)
	, ySpacing_(ySpacing)
	, rows_(rows)
	, cols_(cols)
{
}

/*
TableLayout::~TableLayout()
{
}
*/

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
		(double(bounds.width) - (double(xMargin_) * 2) - (double(xSpacing_) * (double(cols_) - 1))) / double(cols_)));
	const auto elementHeight = int(round(
		(double(bounds.height) - (double(yMargin_) * 2) - (double(ySpacing_) * (double(rows_) - 1))) / double(rows_)));

	int xCount = 0;
	int yCount = 0;
	for (const auto& elem : elements) {

		gfx::Rectangle rect(bounds.x + xMargin_ + ((elementWidth + xSpacing_) * xCount), 
						bounds.y + yMargin_ + ((elementHeight + ySpacing_) * yCount),
						elementWidth,
						elementHeight);
		elem->setRect(rect);

		xCount++;
		if (xCount == cols_) {
			xCount = 0;
			yCount++;
		}

	}
}