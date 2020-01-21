#include "WIN_TableLayout.h"

using namespace win;

TableLayout::TableLayout(int rows, int cols)
	: rows_(rows)
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
	childWidth_ = (int)round(((double)rect.width - ((double)xmargin_ * 2) - ((double)xspacing_ * ((double)cols_ - 1))) / (double)cols_);
	childHeight_ = (int)round(((double)rect.height - ((double)ymargin_ * 2) - ((double)yspacing_ * ((double)rows_ - 1))) / (double)rows_);

	int xoffset = 0;
	int yoffset = 0;
	for (const auto& child : children) {
		LayoutSubElement element = { child, xmargin_ + (childWidth_ * xoffset), ymargin_ + (childHeight_ * yoffset) };

		xoffset++;
		if (xoffset == cols_) {
			xoffset = 0;
			yoffset++;
		}
	}

}