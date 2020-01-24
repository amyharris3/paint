#include "WIN_UIelement.h"
#include <iostream>

using namespace win;

UIelement::UIelement(gfx::Rectangle rect, const char* name)
	: name_(name)
	, foregroundColour_()
	, backgroundColour_()
	, rect_(rect)
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

void UIelement::getForegroundColour(uint8_t rgba[])
{
	foregroundColour_.getComponents(rgba);
}

void UIelement::getBackgroundColour(uint8_t rgba[])
{
	backgroundColour_.getComponents(rgba);
}

void UIelement::setRect(const gfx::Rectangle& rect)
{
	rect_ = rect;
}


void UIelement::mouseEnter()
{
	std::cout << "The mouse has entered the " << name_ << " window. \n";
}

void UIelement::mouseExit()
{
	std::cout << "The mouse has left the " << name_ << " window. \n";
}

void UIelement::mouseButtonDown(MouseButton, int xPixel, int yPixel)
{

}
