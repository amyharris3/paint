#pragma once

namespace paint
{
	//class DrawFlags;
	
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape() = default;
		Shape(const Shape& that) = default;
		Shape(Shape && that) = default;
		Shape& operator=(const Shape & that) = default;
		Shape& operator=(Shape && that) = default;
	};
}
