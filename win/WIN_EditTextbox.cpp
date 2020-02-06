#include "WIN_pch.h"
#include "WIN_EditTextbox.h"

using namespace win;

EditTextbox::EditTextbox(gfx::Rectangle rect, const char* name, SDL_Renderer* renderer, int const textSize, int const xOffset, int const yOffset)
	: UIelement(rect, name)
	, renderer_(renderer)
	, text_(std::make_shared<gfx::Text>(renderer, gfx::Colour { 0, 0, 0, 0xFF }, "OpenSans-Bold.ttf", textSize, "0"))
    , xOffset_(xOffset)
    , yOffset_(yOffset)
    , isClicked_(false)
{
	setBackgroundColour(gfx::Colour(255, 255, 255, 255));
}

void EditTextbox::click()
{
	isClicked_ = !isClicked_;
}

void EditTextbox::editText(const char* newText) const
{
	text_->changeString(newText);
}

void EditTextbox::editTextAndRerender(std::string & newString)
{
	//filters and checks on the input here
	
	text_->changeString(newString.c_str());

	draw();
	SDL_RenderPresent(renderer_);
}

// Simple text entry, TODO copy, paste, highlight, cursor position, ect
void EditTextbox::takeTextEntry()
{
	bool quit = false;
	bool textChanged = false;
	std::string newString;
	int xMouse { 0 };
	int yMouse { 0 };
	int entryCount{ 0 };
	
	SDL_StartTextInput();
	//Recording text entry
	while(!quit && entryCount < 9)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				// case for esc, quits editing
				if (event.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
					break;
				}
				// case for backspace, deletes last input
				if (event.key.keysym.sym == SDLK_BACKSPACE && newString.length() > 0){
					newString.erase(newString.end() - 1);
					editTextAndRerender(newString);
					textChanged = true;
				}
				// case for ctrl+c (copy)
				// case for ctrl+v (paste)
				// case for enter, finishes text entry
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER){
					quit = true;
				}
				break;
			case SDL_TEXTINPUT:
				// put here any filters here on the input
				editTextAndRerender(newString);
				entryCount++;
				textChanged = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&xMouse, &yMouse);
				if (!getRect().containsPoint(xMouse, yMouse)){
					quit = true;
				}
				break;
			default:
				break;
			}
		}
	}

	if (textChanged){
		editTextAndRerender(newString);
	}
}

void EditTextbox::draw()
{
	SDL_Rect outlineRect = { getRect().x-2, getRect().y-2, getRect().width+4, getRect().height+4 };
	SDL_SetRenderDrawColor(renderer_, 0,0,0,255);
	SDL_RenderFillRect(renderer_, &outlineRect);
	
	SDL_Rect boxRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	uint8_t rgba[4];
	getBackgroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);

	(void)text_->renderText(getRect().x + xOffset_, getRect().y + yOffset_);

}

bool EditTextbox::mouseButtonDown(win::MouseButton const button)
{
	isClicked_ = true;
	return false;
}

bool EditTextbox::mouseButtonUp(win::MouseButton const button)
{
	if (isClicked_) {
		printf("Taking text entry now\n");
		takeTextEntry();
		printf("Finished taking text entry\n");
		isClicked_ = false;
	}
	return true;
}