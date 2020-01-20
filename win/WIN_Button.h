#pragma once
#include "WIN_UIelement.h"

namespace win
{
	class Button :
		public UIelement
	{
	public:
		Button();
		virtual ~Button() = default;
		Button(const Button& that) = default;
		Button(Button&& that) = default;
		Button& operator=(const Button& that) = default;
		Button& operator=(Button&& that) = default;

		void draw() override;

	};
}
