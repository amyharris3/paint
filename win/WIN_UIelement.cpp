#include "WIN_UIelement.h"
#include <iostream>
#include "WIN_Container.h"

using namespace win;

UIelement::UIelement(gfx::Rectangle const rect, const char* name)
	: name_(name)
	, foregroundColour_()
	, backgroundColour_()
	, rect_(rect)
	, parent_(nullptr)
{
}

void UIelement::setForegroundColour(gfx::Colour const fgColour)
{
	foregroundColour_ = fgColour;
}


void UIelement::setBackgroundColour(gfx::Colour const bgColour)
{
	backgroundColour_ = bgColour;
}

void UIelement::getForegroundColour(uint8_t rgba[]) const
{
	foregroundColour_.getComponents(rgba);
}

void UIelement::getBackgroundColour(uint8_t rgba[]) const
{
	backgroundColour_.getComponents(rgba);
}

void UIelement::swapFgBgColours()
{
	std::swap(foregroundColour_, backgroundColour_);
}

void UIelement::setRect(const gfx::Rectangle& rect)
{
	rect_ = rect;
}


bool UIelement::mouseEnter()
{
	std::cout << "The mouse has entered the " << name_ << " UI element. \n";
	return false;
}

bool UIelement::mouseExit()
{
	std::cout << "The mouse has left the " << name_ << " UI element. \n";
	return false;
}

bool UIelement::mouseButtonDown(MouseButton button)
{
	return false;
}

void UIelement::setParent(UIelement * parent)
{
	parent_ = parent;
}