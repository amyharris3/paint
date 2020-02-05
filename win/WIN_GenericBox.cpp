#include "WIN_GenericBox.h"

using namespace win;

GenericBox::GenericBox(gfx::Rectangle& rect, const char* name, gfx::Colour foregroundColour, gfx::Colour backgroundColour, gfx::Renderer* renderer)
	: UIelement(rect, name)
	, renderer_(renderer)
{
	this->setForegroundColour(foregroundColour);
	this->setBackgroundColour(backgroundColour);
}

void GenericBox::draw()
{
	renderer_->renderBox(getRect(), getBackgroundColour());
}