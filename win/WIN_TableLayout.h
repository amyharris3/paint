#pragma once

#include "WIN_Layout.h"

namespace win
{
	class UIelement;

	class TableLayout final :
		public Layout
	{
	public:
		explicit TableLayout(int xMargin = 0, int yMargin = 0, int xSpacing = 0, int ySpacing = 0, int rows = 1, int cols = 1);
		~TableLayout() = default;
		TableLayout(TableLayout const& that) = default;
		TableLayout(TableLayout && that) = default;
		TableLayout& operator=(TableLayout const& that) = default;
		TableLayout& operator=(TableLayout && that) = default;

		void setRows(int rows);
		void setCols(int cols);
		
		int getXMargin() const { return xMargin_; }
		int getYMargin() const { return yMargin_; }
		int getXSpacing() const { return xSpacing_; }
		int getYSpacing() const { return ySpacing_; }
		int getRows() const { return rows_; }
		int getCols() const { return cols_; }

		void Apply(std::vector<std::shared_ptr<UIelement>> const& elements, gfx::Rectangle const& bounds) override;

	private:
		int xMargin_;
		int yMargin_;

		int xSpacing_;
		int ySpacing_;

		int rows_;
		int cols_;

	};
}
