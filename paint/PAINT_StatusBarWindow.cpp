#include "PAINT_StatusBarWindow.h"

using namespace paint;

StatusBarWindow::StatusBarWindow(gfx::Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name)
	, xMouse(0)
	, yMouse(0)
	, mouseCoordsText_(gfx::Colour(0,0,0,255),"OpenSans-Regular.ttf", 16, "(0,0)")
{
}

void StatusBarWindow::displayMouseCoords(int x, int y)
{

	//The current input text.
	//std::string inputText = "Some Text";
	//gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColour_);

	SDL_GetMouseState(&x, &y);
	char text[20];
	sprintf_s(text,"(%d,%d)", x, y);
	mouseCoordsText_.changeString(text);
	mouseCoordsText_.render(getRenderer(), getRect().x + getRect().width - mouseCoordsText_.getWidth() - 10, getRect().y + 5);
}

// Status bar should contain only text
void StatusBarWindow::draw()
{
	getRenderer()->renderBox(getRect(), getBackgroundColour());
	displayMouseCoords(xMouse, yMouse);
}