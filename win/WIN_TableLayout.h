#pragma once

#include "WIN_Layout.h"

namespace win
{
	class TableLayout :
		public Layout
	{
	private:
		int rows_;
		int cols_;
		

	public:
		TableLayout() = default;
		TableLayout(int rows, int cols);
		virtual ~TableLayout();

		void setRows(int rows);
		void setCols(int cols);


		void Apply(std::vector<std::shared_ptr<UIelement>> children, gfx::Rectangle rect);

	};
}
