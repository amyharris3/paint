#include "WIN_pch.h"
#include "WIN_UIelement.h"

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


bool UIelement::mouseEnter(bool clicked)
{
	#ifdef VERBOSE
	std::cout << "The mouse has entered the " << name_ << " UI element. \n";
	#endif
	return false;
}

bool UIelement::mouseExit(bool clicked)
{
	#ifdef VERBOSE
	std::cout << "The mouse has left the " << name_ << " UI element. \n";
	#endif
	return false;
}

void UIelement::setParent(UIelement * parent)
{
	parent_ = parent;
}