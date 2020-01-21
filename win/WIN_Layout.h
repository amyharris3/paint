#pragma once

#include "WIN_UIelement.h"
#include <memory>
#include <vector>

namespace win
{
	struct LayoutSubElement
	{
		std::shared_ptr<UIelement> UIelem_;
		int xpos_;
		int ypos_;
	};

	class Layout
	{
	protected:
		int xmargin_;
		int ymargin_;

		int xspacing_;
		int yspacing_;

		int childWidth_;
		int childHeight_;

		//std::vector<int> xpos_;
		//std::vector<int>ypos_;

		std::vector<LayoutSubElement> SubElements_;

	public:
		Layout() = default;
		Layout(const int xmargin, const  int ymargin, const int xspacing, const int yspacing, const int childHeight, const int childWidth);
		virtual ~Layout();

		void setXMargin(int xmargin);
		void setYMargin(int ymargin);
		void setXSpacing(int xspacing);
		void setYSpacing(int yspacing);

		virtual void Apply(std::vector<std::shared_ptr<UIelement>> children, gfx::Rectangle rect);


	};
}
