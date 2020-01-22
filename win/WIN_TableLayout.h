#pragma once

#include "WIN_Layout.h"

namespace win
{
	class UIelement;

	class TableLayout :
		public Layout
	{
	private:
		int xmargin_;
		int ymargin_;

		int xspacing_;
		int yspacing_;

		int rows_;
		int cols_;

	public:
		TableLayout() = default;
		TableLayout(const int xmargin, const int ymargin, const int xspacing, const int yspacing, int rows, int cols);
		virtual ~TableLayout();

		void setRows(int rows);
		void setCols(int cols);
		
		int getXmargin() { return xmargin_; }
		int getYmargin() { return ymargin_; }
		int getXspacing() { return xspacing_; }
		int getYspacing() { return yspacing_; }
		int getRows() { return rows_; }
		int getCols() { return cols_; }

		void Apply(std::vector<std::shared_ptr<UIelement>> const& elements, gfx::Rectangle const& bounds);

	};
}