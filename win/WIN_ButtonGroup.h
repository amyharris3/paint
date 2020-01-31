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

		void addButtonChild(std::shared_ptr<ToggleButton> const& child);
		std::vector<std::shared_ptr<ToggleButton>> getButtonChildren() const { return buttonChildren_; }
		void turnOffOtherChildren();
		void setSelectedChild(ToggleButton* child);
		

	private:
		std::vector<std::shared_ptr<ToggleButton>> buttonChildren_;
		ToggleButton * selectedChild_;
	};


}
