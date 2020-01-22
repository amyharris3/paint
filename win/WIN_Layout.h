#pragma once

#include <memory>
#include <vector>

namespace gfx {
	class Rectangle;
}

namespace win
{
	class UIelement;

	// Layouts take the children in given container and the boundaries of the container (in form of Rectangle),
	// and modify the (x,y,width,height) of the child container to fit the layout. 
	class Layout
	{
	public:
		virtual void Apply(std::vector<std::shared_ptr<UIelement>> const& elements, gfx::Rectangle const& bounds) = 0;

	protected:
		Layout() = default;
		virtual ~Layout() = default;
		Layout(Layout const& that) = default;
		Layout(Layout && that) = default;
		Layout& operator=(Layout const& that) = default;
		Layout& operator=(Layout && that) = default;
	};
}
