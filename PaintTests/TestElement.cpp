#include "pch.h"
#include "TestElement.h"

using namespace PaintTests;

TestElement::TestElement() 
	: UIelement(gfx::Rectangle(), "dummy")
{
	this->setForegroundColour(gfx::Colour(0, 1, 2, 3));
	this->setBackgroundColour(gfx::Colour(250, 251, 252, 253));
}


/*TestElement::TestElement()
	: rect_(gfx::Rectangle())
	, foregroundColour_(gfx::Colour(255,255,255,255))
	, backgroundColour_(gfx::Colour(255, 255, 255, 255))
	, name_("dummy")
{
}*/