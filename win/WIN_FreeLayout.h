#pragma once
#include "WIN_Layout.h"

namespace win
{
	// FreeLayout does not change the parameters of the child elements
	class FreeLayout final : public Layout
	{
	public:
		FreeLayout();
		virtual ~FreeLayout();
		FreeLayout(FreeLayout const& that) = default;
		FreeLayout(FreeLayout&& that) = default;
		FreeLayout& operator=(FreeLayout const& that) = default;
		FreeLayout& operator=(FreeLayout && that) = default;

		void Apply(std::vector<std::shared_ptr<UIelement>> const& elements, gfx::Rectangle const& bounds) override;
	};
}
