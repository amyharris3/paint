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
		ColourValueTextbox(gfx::Rectangle rect, const char* name, SDL_Renderer* renderer, int const textSize, int const xOffset, int const yOffset, uint8_t* linkedVariable);
		~ColourValueTextbox() = default;
		ColourValueTextbox(const ColourValueTextbox& that) = default;
		ColourValueTextbox(ColourValueTextbox&& that) = default;
		ColourValueTextbox& operator=(const ColourValueTextbox& that) = default;
		ColourValueTextbox& operator=(ColourValueTextbox&& that) = default;

		void redirectLinkedVariable(uint8_t* newVariable);
		void valueChangedByTextEntry();
		void valueChangedExternally(); //TODO

		static bool filterNumerical(const char c[]);
		void editTextAndRerender(std::string newString) override;
		void takeTextEntry() override;

		bool mouseButtonUp(win::MouseButton const button) override;

	private:

		uint8_t* linkedVariable_;
		
	};
}
