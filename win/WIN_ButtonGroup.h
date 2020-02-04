#pragma once
#include <vector>
#include <memory>

namespace win
{

	class ToggleButton;
	
	class ButtonGroup
	{
	public:
		ButtonGroup();
		~ButtonGroup() = default;
		ButtonGroup(const ButtonGroup& that) = default;
		ButtonGroup(ButtonGroup&& that) = default;
		ButtonGroup& operator=(const ButtonGroup& that) = default;
		ButtonGroup& operator=(ButtonGroup&& that) = default;

		void addButtonChild(std::weak_ptr<ToggleButton> const& child);
		const std::vector<std::weak_ptr<ToggleButton>>& getButtonChildren() const { return buttonChildren_; }
		void setSelectedChildAndTurnOffOthers(ToggleButton* child);
		
	private:
		std::vector<std::weak_ptr<ToggleButton>> buttonChildren_;
		ToggleButton * selectedChild_;
	};


}
