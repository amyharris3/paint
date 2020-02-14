#include "WIN_pch.h"
#include "WIN_ColourValueTextbox.h"
#include "WIN_Utils.h"

using namespace win;

ColourValueTextbox::ColourValueTextbox(const gfx::Rectangle rect, const char* name, int const textSize, int const xOffset, int const yOffset, uint8_t* linkedVariablePrimary, uint8_t* linkedVariableSecondary, const bool primaryActive)
	: EditTextbox(rect, name, textSize, xOffset, yOffset)
	, linkedVariablePrimary_(linkedVariablePrimary)
	, linkedVariableSecondary_(linkedVariableSecondary)
	, primaryActive_(primaryActive)
	, rerenderFlag_(false)
{
	assert(linkedVariablePrimary_);
	assert(linkedVariableSecondary_);
	
	setBackgroundColour(gfx::Colour(255, 255, 255, 255));
	valueChangedExternally();
}

void ColourValueTextbox::primaryActiveSwitch()
{
	primaryActive_ = !primaryActive_;
	if (primaryActive_) {
		editText(std::to_string(*linkedVariablePrimary_).c_str());
	}
	else {
		editText(std::to_string(*linkedVariableSecondary_).c_str());
	}
}

void ColourValueTextbox::valueChangedByTextEntry()
{
	if (primaryActive_) {
		*linkedVariablePrimary_ = std::stoi(getText()->getString());
	}
	else{
		*linkedVariableSecondary_ = std::stoi(getText()->getString());
	}

	rerenderFlag_ = true;
}

void ColourValueTextbox::valueChangedExternally()
{
	if (primaryActive_) {
		editText(std::to_string(*linkedVariablePrimary_).c_str());
	}
	else {
		editText(std::to_string(*linkedVariableSecondary_).c_str());
	}
	
	rerenderFlag_ = true;
}

void ColourValueTextbox::editText(const char* newText)
{
	getText()->changeString(newText);
	valueChangedByTextEntry();
}

void ColourValueTextbox::editTextAndRerender(std::string & newString)
{
	if (std::stoi(newString) < 0) {
		newString = "0";
	}

	if (std::stoi(newString) > 255) {
		newString = "255";
	}

	//getText()->changeString(newString.c_str());
	editText(newString.c_str());

	rerenderFlag_ = true;
}

void ColourValueTextbox::takeTextEntry()
{
	auto quit = false;
	auto textChanged = false;
	std::string newString;
	auto xMouse = 0;
	auto yMouse = 0;
	auto entryCount = 0;

	SDL_StartTextInput();
	//Recording text entry
	while (!quit && entryCount < 20)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				// case for esc, quits text editing immediately
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					break;
				}
				// case for backspace, deletes last input
				if (event.key.keysym.sym == SDLK_BACKSPACE && newString.length() > 0) {
					newString.erase(newString.end() - 1);
					this->editTextAndRerender(newString);
					textChanged = true;
				}
				// case for ctrl+c (copy)
				// case for ctrl+v (paste)
				// case for enter, finishes text entry
				else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
					quit = true;
				}
				else {
					entryCount++;
				}
				break;
			case SDL_TEXTINPUT:
#ifdef VERBOSE
				printf("IN: %s\n", event.text.text);
#endif
				if (win::utils::filterNumerical(*(event.text.text))) {
					newString += event.text.text;
					this->editTextAndRerender(newString);
					textChanged = true;
				}
				entryCount++;
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&xMouse, &yMouse);
				if (!getRect().containsPoint(xMouse, yMouse)) {
					quit = true;
				}
				break;
			default:
				break;
			}
		}
	}

	while (newString.length() > 1 && newString.front() == '0') {
		newString.erase(0, 1);
	}
	
	if (textChanged) {
		this->editTextAndRerender(newString);
	}
}

bool ColourValueTextbox::mouseButtonUp(win::MouseButton const button, bool clicked, win::SDLRenderer* renderer)
{
	if (getClick()) {
#ifdef VERBOSE
		printf("Taking text entry now\n");
#endif
		this->takeTextEntry();
#ifdef VERBOSE
		printf("Finished taking text entry\n");
#endif
		click();
	}

	return true;
}