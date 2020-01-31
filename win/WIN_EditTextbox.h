#pragma once
#include "WIN_UIelement.h"
#include "SDL.h"
#include "SDL_ttf.h"
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
		EditTextbox(gfx::Rectangle rect, const char* name, SDL_Renderer* renderer, int const textSize, int const xOffset, int const yOffset);
		~EditTextbox() = default;
		EditTextbox(const EditTextbox & that) = default;
		EditTextbox(EditTextbox && that) = default;
		EditTextbox& operator=(const EditTextbox & that) = default;
		EditTextbox& operator=(EditTextbox && that) = default;

		SDL_Renderer* getRenderer() const { return renderer_;  }
		std::shared_ptr<gfx::Text> getText() const { return text_; }
		bool getClick() const { return isClicked_; }
		void click();

		void editText(const char* newText);
		virtual void editTextAndRerender(std::string newString);
		virtual void takeTextEntry();
		
		void draw() override;
		void mouseButtonDown(win::MouseButton const button) override;
		void mouseButtonUp(win::MouseButton const button) override;
		
	private:

		SDL_Renderer* renderer_;
		std::shared_ptr<gfx::Text> text_;
		int xOffset_;
		int yOffset_;

		//ought to define the linked variable in the derived classes
		
		//dirty flags
		bool isClicked_;
		
	};
}
