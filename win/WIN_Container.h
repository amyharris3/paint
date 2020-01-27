#pragma once

#include "WIN_UIelement.h"
#include "WIN_Layout.h"
#include <memory>
#include <vector>

namespace win
{
	//class Layout;

	// Every container now needs to have a layout, or cannot draw
	class Container : public UIelement
	{
	public:
		
		
		// Lifecycle
		Container() = delete;
		Container(std::shared_ptr<Layout> layout, const gfx::Rectangle& rect, const char* name);
		~Container() = default;
		Container(const Container& that) = default;
		Container(Container&& that) = default;
		Container& operator=(const Container& that) = default;
		Container& operator=(Container&& that) = default;

		void AddChild(std::shared_ptr<UIelement> child);
		const std::vector<std::shared_ptr<UIelement>> & getChildren() { return children_; }

		void draw() override;
		void applyLayout() const;

	private:
		std::vector<std::shared_ptr<UIelement>> children_;
		std::shared_ptr<Layout> layout_;
		gfx::Rectangle rect_;
		bool dirty_;
	};
}
