#include "PAINT_StatusBarWindow.h"

using namespace paint;

StatusBarWindow::StatusBarWindow(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, gfx::Rectangle const& rect, const char* name)
	: Window(sdlWindow, renderer, surface, rect, name)
{
}

void StatusBarWindow::displayMouseCoords(int xMouse, int yMouse)
{

	//The current input text.
	//std::string inputText = "Some Text";
	//gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColour_);

}