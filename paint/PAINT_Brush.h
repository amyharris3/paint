#pragma once

namespace paint
{
	struct Coords;

	class Brush 
	{
	public:
		Brush() = delete;
		explicit Brush(int thickness);
		~Brush() = default;
		Brush(const Brush& that) = default;
		Brush(Brush&& that) = default;
		Brush& operator=(const Brush& that) = default;
		Brush& operator=(Brush&& that) = default;
		void setThickness(int thickness);
		int getThickness() const { return thickness_; }

	private:
		int thickness_;
	};
}

