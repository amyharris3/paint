#include "WIN_pch.h"
#include "WIN_Container.h"
#include "WIN_FreeLayout.h"

using namespace win;

Container::Container()
	: Container(std::make_shared<FreeLayout>(), gfx::Rectangle(), "container")
{
}

Container::Container(std::shared_ptr<Layout> layout, const gfx::Rectangle& rect, const char* name)
	: UIelement(rect, name)
	, layout_(std::move(layout))
	//, rect_(rect)
	, dirty_(false)
{
}

void Container::addChild(std::shared_ptr<UIelement> const & child)
{
	children_.push_back(child);
	child->setParent(this);
	dirty_ = true;
}

/* override */
void Container::draw()
{
	if (dirty_) {
		layout_->Apply(children_, getRect());
		dirty_ = false;
	}

	for (auto & child : children_) {
		child->draw();
	}
}

void Container::applyLayout() const
{
	layout_->Apply(children_, getRect());
}
