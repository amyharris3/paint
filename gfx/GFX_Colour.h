#pragma once

namespace gfx
{
	class Colour
	{
	private:
		int r_;
		int g_;
		int b_;
		int a_;
	public:
		Colour() = default;
		Colour(int r, int g, int b, int a);
		~Colour() = default;

		int* getColour();
	};
}
