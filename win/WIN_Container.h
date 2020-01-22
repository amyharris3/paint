#pragma once

#include "WIN_UIelement.h"
#include "WIN_Layout.h"
#include "WIN_TableLayout.h"
#include <memory>
#include <vector>

namespace win
{
	//class Layout;

	class Container : public UIelement
	{
	public:
		
		
		// Lifecycle
		Container() = default;
		Container(std::shared_ptr<Layout> layout, const gfx::Rectangle& rect, const char* name);
		~Container() = default;
		Container(const Container& that) = default;
		Container(Container&& that) = default;
		Container& operator=(const Container& that) = default;
		Container& operator=(Container&& that) = default;

		void AddChild(std::shared_ptr<UIelement> child);
		void ApplyLayout();
		std::vector<std::shared_ptr<UIelement>> getChildren() { return children_; }


		void draw() override;

	private:
		std::vector<std::shared_ptr<UIelement>> children_;
		std::shared_ptr<Layout> layout_;
		gfx::Rectangle rect_;
		const char* name_;
	};
}
