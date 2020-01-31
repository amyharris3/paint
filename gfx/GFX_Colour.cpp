#include "GFX_Colour.h"

using namespace gfx;

Colour::Colour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
	: r_(r)
	, g_(g)
	, b_(b)
	, a_(a)
{
}

void Colour::getComponents(uint8_t rgba[])
{
	rgba[0] = r_;
	rgba[1] = g_;
	rgba[2] = b_;
	rgba[3] = a_;
}
