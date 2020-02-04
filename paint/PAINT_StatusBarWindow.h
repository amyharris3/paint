#pragma once

#include "WIN_Window.h"

namespace paint
{
	class StatusBarWindow final : public win::Window
	{
	public:
		StatusBarWindow() = delete;
		StatusBarWindow(SDL_Renderer* renderer, gfx::Rectangle const& rect, const char* name);
		virtual ~StatusBarWindow() = default;
		StatusBarWindow(const StatusBarWindow& that) = delete;
		StatusBarWindow(StatusBarWindow && that) = delete;
		StatusBarWindow& operator=(const StatusBarWindow & that) = delete;
		StatusBarWindow& operator=(StatusBarWindow && that) = delete;

	};
}
