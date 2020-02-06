#pragma once

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
		uint8_t getRed() const { return r_; }
		uint8_t getGreen() const { return g_; }
		uint8_t getBlue() const { return b_; }
		uint8_t getAlpha() const { return a_; }
		
	private:
		uint8_t r_;
		uint8_t g_;
		uint8_t b_;
		uint8_t a_;
	};
}