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

		uint8_t* getLinkedPrimary() const { return linkedVariablePrimary_; }
		uint8_t* getLinkedSecondary() const { return linkedVariableSecondary_; }
		
		void valueChangedByTextEntry();
		void valueChangedExternally(); //TODO

		void editText(const char* newText) override;
		void editTextAndRerender(std::string & newString) override;
		void takeTextEntry() override;

		void primaryActiveSwitch();
		
		bool mouseButtonUp(MouseButton button, bool clicked) override;

	private:

		uint8_t* linkedVariablePrimary_;
		uint8_t* linkedVariableSecondary_;
		bool primaryActive_; //else secondary is active
		bool rerenderFlag_;
		
	};
}
