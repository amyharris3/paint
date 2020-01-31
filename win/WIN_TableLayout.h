#pragma once

#include "WIN_Layout.h"

namespace win
{
	class UIelement;

	class TableLayout final :
		public Layout
	{
	public:
		explicit TableLayout(const int xmargin = 0, const int ymargin = 0, const int xspacing = 0, const int yspacing = 0, int rows = 1, int cols = 1);
		virtual ~TableLayout() = default;
		TableLayout(TableLayout const& that) = default;
		TableLayout(TableLayout && that) = default;
		TableLayout& operator=(TableLayout const& that) = default;
		TableLayout& operator=(TableLayout && that) = default;

		void setRows(int rows);
		void setCols(int cols);
		
		int getXmargin() const { return xmargin_; }
		int getYmargin() const { return ymargin_; }
		int getXspacing() const { return xspacing_; }
		int getYspacing() const { return yspacing_; }
		int getRows() const { return rows_; }
		int getCols() const { return cols_; }

		void Apply(std::vector<std::shared_ptr<UIelement>> const& elements, gfx::Rectangle const& bounds) override;

	private:
		int xmargin_;
		int ymargin_;

		int xspacing_;
		int yspacing_;

		int rows_;
		int cols_;

	};
}
