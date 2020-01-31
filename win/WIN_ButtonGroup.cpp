#include "WIN_ButtonGroup.h"
#include "WIN_Button.h"
#include "WIN_ToggleButton.h"

using namespace win;

ButtonGroup::ButtonGroup()
{
	selectedChild_ = nullptr;
}


void ButtonGroup::addButtonChild(std::shared_ptr<ToggleButton> const& child)
{
	buttonChildren_.push_back(child);
}

void ButtonGroup::turnOffOtherChildren()
{
	for (auto child : buttonChildren_) {
		if (child.get() != selectedChild_) {
			child->turnOff();
		}
	}
}

void ButtonGroup::setSelectedChild(ToggleButton* child)
{
	selectedChild_ = child;
}

