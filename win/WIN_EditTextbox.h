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
		EditTextbox(gfx::Rectangle rect, const char* name, SDL_Renderer* renderer, int const textSize, int const xOffset, int const yOffset, std::shared_ptr<int> linkedVariable);
		~EditTextbox() = default;
		EditTextbox(const EditTextbox & that) = default;
		EditTextbox(EditTextbox && that) = default;
		EditTextbox& operator=(const EditTextbox & that) = default;
		EditTextbox& operator=(EditTextbox && that) = default;

		static char filterNumerical(const char c[]);
		void updateAndRerender(std::string newString);
		void takeTextEntry();
		
		void draw() override;
		void mouseButtonDown(win::MouseButton const button) override;
		void mouseButtonUp(win::MouseButton const button) override;
		
	private:

		SDL_Renderer* renderer_;
		gfx::Text text_;
		int xOffset_;
		int yOffset_;
		
		std::shared_ptr<int> linkedVariable_;

		//dirty flags
		bool isClicked_;
		
	};
}
