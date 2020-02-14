#include "WIN_pch.h"
#include "WIN_GenericBox.h"
#include "WIN_SDLRenderer.h"

using namespace win;

GenericBox::GenericBox(gfx::Rectangle& rect, const char* name, const gfx::Colour foregroundColour, const gfx::Colour backgroundColour)
	: UIelement(rect, name)
{
	this->setForegroundColour(foregroundColour);
	this->setBackgroundColour(backgroundColour);
}

void GenericBox::draw(win::SDLRenderer* renderer)
{
	renderer->renderBox(gfx::RenderTarget::SCREEN, getRect(), getBackgroundColour());
}