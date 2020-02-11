#pragma once
#include "WIN_UIelement.h"
#include <string>
#include <memory>
#include "GFX_Text.h"

namespace win
{
	// Editable textbox, displays text and user can input text to update the variable it is linked to
	// Currently working only with integer variables
	class EditTextbox : public UIelement
	{
	public:
		EditTextbox() = delete;
		EditTextbox(gfx::Rectangle rect, const char* name, gfx::Renderer* renderer, int textSize, int xOffset, int yOffset);
		EditTextbox(gfx::Rectangle rect, const char* name, gfx::Renderer* renderer, int textSize, int xOffset, int yOffset, const char* initialText);
		~EditTextbox() = default;
		EditTextbox(const EditTextbox & that) = default;
		EditTextbox(EditTextbox && that) = default;
		EditTextbox& operator=(const EditTextbox & that) = default;
		EditTextbox& operator=(EditTextbox && that) = default;

		gfx::Renderer* getRenderer() const { return renderer_;  }
		std::shared_ptr<gfx::Text> getText() const { return text_; }
		int getXOffset() const { return xOffset_; }
		int getYOffset() const { return yOffset_; }
		bool getClick() const { return isClicked_; }
		void click();

		virtual void editText(const char* newText);
		virtual void editTextAndRerender(std::string & newString);
		virtual void takeTextEntry();
		
		void draw() override;
		bool mouseButtonDown(MouseButton button, bool clicked) override;
		bool mouseButtonUp(MouseButton button, bool clicked) override;
		
	private:

		gfx::Renderer* renderer_;
		std::shared_ptr<gfx::Text> text_;
		int xOffset_;
		int yOffset_;

		//ought to define the linked variable in the derived classes
		
		//dirty flags
		bool isClicked_;
		
	};
}
