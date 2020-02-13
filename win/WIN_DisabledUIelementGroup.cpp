#include "WIN_pch.h"
#include "WIN_DisabledUIelementGroup.h"
#include "WIN_UIelement.h"

using namespace win;


void DisabledUIelementGroup::addChild(std::weak_ptr<win::UIelement> const& child)
{
	disChildren_.push_back(child);
}

void DisabledUIelementGroup::toggleDisableChildren(bool activated)
{
	for (auto const& child : disChildren_) {
		if (auto childSp = child.lock()) {
			childSp->setActivated(activated);
		}
	}
}

