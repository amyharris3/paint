#include "WIN_EditTextbox.h"
#include "SDL.h"
#include "SDL_ttf.h"

using namespace win;

EditTextbox::EditTextbox(gfx::Rectangle rect, const char* name, SDL_Renderer* renderer, int const textSize, int const xOffset, int const yOffset, std::shared_ptr<int> linkedVariable)
	: UIelement(rect, name)
	, renderer_(renderer)
	, text_(renderer, { 0, 0, 0, 0xFF }, "OpenSans-Bold.ttf", textSize,"100")
	, xOffset_(xOffset)
	, yOffset_(yOffset)
	, linkedVariable_(std::move(linkedVariable))
	, isClicked_(false)
{
	setBackgroundColour(gfx::Colour(255, 255, 255, 255));
}

char EditTextbox::filterNumerical(const char c[])
{
	//slightly more efficient
	//if (*c > '/' && *c < ':'){
	if (*c >= '0' && *c <= '9'){
		return *c;
	}
	else {
		// should return null char
		return 0;
	}
}

void EditTextbox::updateAndRerender(std::string newString)
{
	if (std::stoi(newString) < 0) {
		newString = "0";
	}

	if (std::stoi(newString) > 255) {
		newString = "255";
	}

	text_.updateString(newString.c_str());

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
					updateAndRerender(newString);
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
				newString += filterNumerical(event.text.text);
				updateAndRerender(newString);
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
		updateAndRerender(newString);
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

	auto renderSuccess = text_.renderText(getRect().x + xOffset_, getRect().y + yOffset_);

}

void EditTextbox::mouseButtonDown(win::MouseButton const button)
{
	isClicked_ = true;
}

void EditTextbox::mouseButtonUp(win::MouseButton const button)
{
	if (isClicked_) {
		printf("Taking text entry now\n");
		takeTextEntry();
		printf("Finished taking text entry\n");
		isClicked_ = false;
	}
}