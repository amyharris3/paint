#pragma once

namespace paint
{

	class Brush 
	{
		/* Creates a brush with thickness of possible values 0, 1 or 2.
		A brush with thickness 0 is 1 pixel wide. A brush with thickness
		1 is 3 pixels wide, and a brush with thickness 2 is 5 pixels wide. */
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

