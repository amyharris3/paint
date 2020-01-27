#pragma once

namespace paint
{
	class Tool
	{
	public:
		Tool() = default;
		virtual ~Tool() = default;
		Tool(const Tool& that) = default;
		Tool(Tool && that) = default;
		Tool& operator=(const Tool & that) = default;
		Tool& operator=(Tool && that) = default;
	};
}
