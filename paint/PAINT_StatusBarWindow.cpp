#include "PAINT_StatusBarWindow.h"

using namespace paint;

StatusBarWindow::StatusBarWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name)
	, xMouse(0)
	, yMouse(0)
	, mouseCoordsText_(getRenderer(), gfx::Colour(0,0,0,255),"OpenSans-Regular.ttf", 16, "(0,0)")
{
}

void StatusBarWindow::displayMouseCoords(int xMouse, int yMouse)
{

	//The current input text.
	//std::string inputText = "Some Text";
	//gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColour_);

	SDL_GetMouseState(&xMouse, &yMouse);
	char text[20];
	sprintf_s(text,"(%d,%d)", xMouse, yMouse);
	mouseCoordsText_.changeString(text);
	mouseCoordsText_.renderText(getRect().x + getRect().width - mouseCoordsText_.getWidth() - 10, getRect().y + 5);
}

// Status bar should contain only text
void StatusBarWindow::draw()
{
	const auto& rect = getRect();
	SDL_Rect sdlRect{ rect.x, rect.y, rect.width, rect.height };
	SDL_RenderDrawRect(getRenderer(), &sdlRect);
	uint8_t colourArr[4];
	getBackgroundColour().getComponents(colourArr);
	SDL_SetRenderDrawColor(getRenderer(), colourArr[0], colourArr[1], colourArr[2], colourArr[3]);
	SDL_RenderFillRect(getRenderer(), &sdlRect);

	displayMouseCoords(xMouse, yMouse);
}