#include "WIN_Container.h"
#include "WIN_FreeLayout.h"

using namespace win;

//Container::Container()
//	: Container(std::make_shared<FreeLayout>(), rect_)
//{
//}

Container::Container(std::shared_ptr<Layout> layout, const gfx::Rectangle& rect, const char* name)
	: UIelement(rect, name)
	, layout_(std::move(layout))
	, rect_(rect)
	, dirty_(false)
{

}

void Container::addChild(std::shared_ptr<UIelement> const & child)
{
	children_.push_back(child);
	dirty_ = true;
}

void Container::draw()
{
	if (dirty_) {
		layout_->Apply(children_, getRect());
		dirty_ = false;
	}

	// TODO: draw myself.
	for (auto & child : children_) {
		auto name = child->getName();
		gfx::Rectangle r = child->getRect();
		child->draw();
	}
}

void Container::applyLayout() const
{
	layout_->Apply(children_, getRect());
}
