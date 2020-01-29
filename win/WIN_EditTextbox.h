#pragma once
#include "WIN_UIelement.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <memory>

namespace win
{
	// Editable textbox, displays text and user can input text to update the variable it is linked to
	// Currently working only with integer variables
	class EditTextbox : public UIelement
	{
	public:
		EditTextbox() = delete;
		EditTextbox(gfx::Rectangle rect, const char* name, SDL_Renderer* renderer, std::shared_ptr<int> linkedVariable);
		~EditTextbox() = default;
		EditTextbox(const EditTextbox & that) = default;
		EditTextbox(EditTextbox && that) = default;
		EditTextbox& operator=(const EditTextbox & that) = default;
		EditTextbox& operator=(EditTextbox && that) = default;

		bool renderText();
		
		void draw() override;

	private:

		SDL_Renderer* renderer_;
		TTF_Font* textFont_;
		SDL_Color textColour_;
		SDL_Texture* textTex_;
		std::string loadedText_;

		std::shared_ptr<int> linkedVariable_;

	};
}
