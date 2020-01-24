#pragma once

namespace paint
{
	class DrawFlags final
	{
	public:
		DrawFlags() = default;
		~DrawFlags() = default;
		DrawFlags(const DrawFlags& that) = default;
		DrawFlags(DrawFlags && that) = default;
		DrawFlags& operator=(const DrawFlags & that) = default;
		DrawFlags& operator=(DrawFlags && that) = default;
	};
}
