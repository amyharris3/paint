#include "PAINT_pch.h"
#include "PAINT_StatusBarWindow.h"

using namespace paint;

StatusBarWindow::StatusBarWindow(gfx::Renderer* renderer, gfx::Rectangle const& rect, const char* name, const int drawWinX, const int drawWinY)
	: Window(renderer, rect, name)
	, xMouse(0)
	, yMouse(0)
	, mouseCoordsText_(gfx::Colour(0,0,0,255),"OpenSans-Regular.ttf", 16, "(0,0)")
	, outputMessageText_(gfx::Colour(0, 0, 0, 255), "OpenSans-Regular.ttf", 16, "Status Bar Window initialised")
	, drawWinX_(drawWinX)
	, drawWinY_(drawWinY)
{
}

//Absolute mouse coordinates
void StatusBarWindow::displayMouseCoords(int x, int y)
{
	SDL_GetMouseState(&x, &y);
	char textAbs[20];
	sprintf_s(textAbs,"Abs(%d,%d)", x, y);
	mouseCoordsText_.changeString(textAbs);
	mouseCoordsText_.render(getRenderer(), getRect().x + getRect().width - mouseCoordsText_.getWidth() - 10, getRect().y + 5);
}

//Relative mouse coordinates
void StatusBarWindow::displayMouseCoordsRelative(int x, int y)
{
	SDL_GetMouseState(&x, &y);
	char textRel[20];
	sprintf_s(textRel, "Rel(%d,%d)", x - drawWinX_, y - drawWinY_);
	mouseCoordsText_.changeString(textRel);
	mouseCoordsText_.render(getRenderer(), getRect().x + getRect().width - 2 * mouseCoordsText_.getWidth() - 25, getRect().y + 5);
}

// change output message to display on the status bar
void StatusBarWindow::outputMessage(const char* message)
{
	outputMessageText_.changeString(message);
}

// Status bar should contain only text
void StatusBarWindow::draw()
{
	getRenderer()->renderBox(gfx::RenderTarget::SCREEN, getRect(), getBackgroundColour());
	displayMouseCoords(xMouse, yMouse);
	displayMouseCoordsRelative(xMouse, yMouse);
	outputMessageText_.render(getRenderer(), getRect().x + 10, getRect().y + 5);
}