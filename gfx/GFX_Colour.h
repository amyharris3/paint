#pragma once

#include <cstdint>

namespace gfx
{
	class Colour
	{
	public:
		Colour() = default;
		Colour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
		~Colour() = default;
		Colour(Colour const&) = default;
		Colour& operator=(Colour const&) = default;
		Colour(Colour&&) = default;
		Colour& operator=(Colour&&) = default;

		void getComponents(uint8_t rgba[]);
		
	private:
		uint8_t r_;
		uint8_t g_;
		uint8_t b_;
		uint8_t a_;
	};
}