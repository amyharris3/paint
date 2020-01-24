#include "PAINT_StatusBarWindow.h"

using namespace paint;

StatusBarWindow::StatusBarWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name)
	: Window(renderer, rect, name)
{
}

void StatusBarWindow::displayMouseCoords(int xMouse, int yMouse)
{

	//The current input text.
	//std::string inputText = "Some Text";
	//gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColour_);

}