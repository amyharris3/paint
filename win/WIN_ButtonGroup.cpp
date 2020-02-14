#include "WIN_pch.h"
#include "WIN_ButtonGroup.h"
#include "WIN_ToggleButton.h"

using namespace win;

ButtonGroup::ButtonGroup()
	: selectedChild_(nullptr)
{
}

void ButtonGroup::addButtonChild(std::weak_ptr<ToggleButton> const& child)
{
	buttonChildren_.push_back(child);
}

void ButtonGroup::setSelectedChildAndTurnOffOthers(ToggleButton* child)
{
	selectedChild_ = child;
	for (const auto& aChild : buttonChildren_) {
		if (auto childSp = aChild.lock()) {
			if (childSp.get() != selectedChild_) {
				childSp->turnOff();
			}
		}
	}
}

void ButtonGroup::setSelectedChildByIndex(const int index)
{
	setSelectedChildAndTurnOffOthers(getButtonChildren()[index].lock().get());
	getButtonChildren()[index].lock()->turnOn();
}