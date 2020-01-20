#include "WIN_UIelement.h"
#include <iostream>
#include <SDL.h>

using namespace win;

UIelement::UIelement(gfx::Rectangle rect, const char* name)
	: rect_(rect)
	, name_(name)
{
}

void UIelement::setForegroundColour(gfx::Colour fgColour)
{
	foregroundColour_ = fgColour;
}


void UIelement::setBackgroundColour(gfx::Colour bgColour)
{
	backgroundColour_ = bgColour;
}

void UIelement::mouseEnter()
{
	std::cout << "The mouse has entered the " << name_ << " window. \n";
}

void UIelement::mouseExit()
{
	std::cout << "The mouse has left the " << name_ << " window. \n";
}

void UIelement::mouseButtonDown(MouseButton b, int xPixel, int yPixel)
{

}