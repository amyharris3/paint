#include "WIN_ColourValueTextbox.h"

using namespace win;

ColourValueTextbox::ColourValueTextbox(gfx::Rectangle rect, const char* name, SDL_Renderer* renderer, int const textSize, int const xOffset, int const yOffset, uint8_t* linkedVariable)
	: EditTextbox(rect, name, renderer, textSize, xOffset, yOffset)
	, linkedVariable_(linkedVariable)
{
	setBackgroundColour(gfx::Colour(255, 255, 255, 255));
	editText(std::to_string(*linkedVariable_).c_str());
}

void ColourValueTextbox::redirectLinkedVariable(uint8_t* newVariable)
{
	linkedVariable_ = newVariable;
}

void ColourValueTextbox::valueChangedByTextEntry()
{
	*linkedVariable_ = std::stoi(getText()->getString());

	draw();
	SDL_RenderPresent(getRenderer());
}

void ColourValueTextbox::valueChangedExternally()
{
	printf("box linked var %s\n", std::to_string(*linkedVariable_).c_str());
	editText(std::to_string(*linkedVariable_).c_str());
	
	draw();
	SDL_RenderPresent(getRenderer());
}

bool ColourValueTextbox::filterNumerical(const char c[])
{
	//slightly more efficient
	//if (*c > '/' && *c < ':'){
	if ((*c >= '0' && *c <= '9')) {
		return true;
	}
	else {
		return false;
	}
}

void ColourValueTextbox::editTextAndRerender(std::string newString)
{
	if (std::stoi(newString) < 0) {
		newString = "0";
	}

	if (std::stoi(newString) > 255) {
		newString = "255";
	}

	getText()->changeString(newString.c_str());

	draw();
	SDL_RenderPresent(getRenderer());
}

void ColourValueTextbox::takeTextEntry()
{
	bool quit = false;
	bool textChanged = false;
	std::string newString;
	int xMouse = 0;
	int yMouse = 0;
	int entryCount = 0;

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
				printf("IN: %s\n", event.text.text);
				if (filterNumerical(event.text.text)) {
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
		valueChangedByTextEntry();
	}
}

bool ColourValueTextbox::mouseButtonUp(win::MouseButton const button)
{
	if (getClick()) {
		printf("Taking text entry now\n");
		this->takeTextEntry();
		printf("Finished taking text entry\n");
		click();
	}

	return true;
}