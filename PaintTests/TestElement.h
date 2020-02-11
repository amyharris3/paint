#pragma once

#include "WIN_UIelement.h"

namespace PaintTests
{
	class TestElement final : public win::UIelement
	{
	public:
		
		TestElement();
		~TestElement() = default;
		TestElement(TestElement const& that) = default;
		TestElement(TestElement && that) = default;
		TestElement& operator=(TestElement const& that) = default;
		TestElement& operator=(TestElement && that) = default;

		void draw() override {}
	};
}
