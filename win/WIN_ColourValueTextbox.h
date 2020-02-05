#pragma once
#include "WIN_EditTextbox.h"

namespace win
{
	// Editable textbox, displays text and user can input text to update the variable it is linked to
	// Currently working only with integer variables
	class ColourValueTextbox final : public EditTextbox
	{
	public:
		ColourValueTextbox() = delete;
		ColourValueTextbox(gfx::Rectangle rect, const char* name, gfx::Renderer* renderer, int textSize, int xOffset, int yOffset, uint8_t* linkedVariablePrimary, uint8_t* linkedVariableSecondary, bool primaryActive);
		~ColourValueTextbox() = default;
		ColourValueTextbox(const ColourValueTextbox& that) = default;
		ColourValueTextbox(ColourValueTextbox&& that) = default;
		ColourValueTextbox& operator=(const ColourValueTextbox& that) = default;
		ColourValueTextbox& operator=(ColourValueTextbox&& that) = default;

		void valueChangedByTextEntry();
		void valueChangedExternally(); //TODO

		void editTextAndRerender(std::string & newString) override;
		void takeTextEntry() override;

		void primaryActiveSwitch() { primaryActive_ = !primaryActive_; }
		
		bool mouseButtonUp(win::MouseButton button) override;

	private:

		uint8_t* linkedVariablePrimary_;
		uint8_t* linkedVariableSecondary_;
		bool primaryActive_; //else secondary is active
		bool rerenderFlag_;
		
	};
}
