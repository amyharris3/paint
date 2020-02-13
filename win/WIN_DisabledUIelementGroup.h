#pragma once

namespace win
{
	class UIelement;
	
	class DisabledUIelementGroup
	{
	public:
		DisabledUIelementGroup() = default;
		~DisabledUIelementGroup() = default;
		DisabledUIelementGroup(const DisabledUIelementGroup& that) = default;
		DisabledUIelementGroup(DisabledUIelementGroup&& that) = default;
		DisabledUIelementGroup& operator=(const DisabledUIelementGroup& that) = default;
		DisabledUIelementGroup& operator=(DisabledUIelementGroup&& that) = default;

		void addChild(std::weak_ptr<UIelement> const& child);
		void toggleDisableChildren(bool activated);
		std::vector<std::weak_ptr<UIelement>>& getChildren() { return disChildren_; }

	private:
		std::vector<std::weak_ptr<UIelement>> disChildren_;
	};


}

