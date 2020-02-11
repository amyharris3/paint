#include "WIN_pch.h"
#include "WIN_EditTextbox.h"
#include "GFX_Renderer.h"

using namespace win;

EditTextbox::EditTextbox(const gfx::Rectangle rect, const char* name, gfx::Renderer* renderer, int const textSize, int const xOffset, int const yOffset)
	: EditTextbox(rect, name, renderer, textSize, xOffset, yOffset, "")
{
}

EditTextbox::EditTextbox(const gfx::Rectangle rect, const char* name, gfx::Renderer* renderer, int const textSize, int const xOffset, int const yOffset, const char* initialText)
	: UIelement(rect, name)
	, renderer_(renderer)
	, text_(std::make_shared<gfx::Text>(gfx::Colour { 0, 0, 0, 0xFF }, "OpenSans-Bold.ttf", textSize, initialText))
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

void EditTextbox::editText(const char* newText)
{
	text_->changeString(newText);
}

void EditTextbox::editTextAndRerender(std::string & newString)
{
	//filters and checks on the input here
	
	text_->changeString(newString.c_str());

	draw();
	getRenderer()->renderPresent();
}

// Simple text entry, TODO copy, paste, highlight, cursor position, ect
void EditTextbox::takeTextEntry()
{
	auto quit = false;
	auto textChanged = false;
	std::string newString;
	auto xMouse { 0 };
	auto yMouse { 0 };
	auto entryCount{ 0 };
	
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
	renderer_->renderTextbox(getRect(), getBackgroundColour(), text_.get(), xOffset_, yOffset_);
	
}

bool EditTextbox::mouseButtonDown(MouseButton button, bool clicked)
{
	isClicked_ = true;
	return false;
}

bool EditTextbox::mouseButtonUp(MouseButton button, bool clicked)
{
	if (isClicked_) {
		printf("Taking text entry now\n");
		takeTextEntry();
		printf("Finished taking text entry\n");
		isClicked_ = false;
	}
	return true;
}