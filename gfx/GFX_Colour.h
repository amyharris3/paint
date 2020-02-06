#pragma once

#include <cstdint>

namespace gfx
{
	class Colour
	{
	public:
		Colour() = default;
		Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		~Colour() = default;
		Colour(Colour const&) = default;
		Colour& operator=(Colour const&) = default;
		Colour(Colour&&) = default;
		Colour& operator=(Colour&&) = default;

		void getComponents(uint8_t rgba[]) const;
		
	private:
		uint8_t r_;
		uint8_t g_;
		uint8_t b_;
		uint8_t a_;
	};
}