#pragma once

#include "WIN_Window.h"
#include "GFX_Text.h"

namespace paint
{
	class StatusBarWindow final : public win::Window
	{
	public:
		StatusBarWindow() = delete;
		StatusBarWindow(gfx::Renderer* renderer, gfx::Rectangle const& rect, const char* name, const int drawWinX, const int drawWinY);
		virtual ~StatusBarWindow() = default;
		StatusBarWindow(const StatusBarWindow& that) = delete;
		StatusBarWindow(StatusBarWindow && that) = delete;
		StatusBarWindow& operator=(const StatusBarWindow & that) = delete;
		StatusBarWindow& operator=(StatusBarWindow && that) = delete;

		void displayMouseCoords(int x, int y);
		void displayMouseCoordsRelative(int x, int y);


		void draw() override;

	private:	
		
		int xMouse;
		int yMouse;
		gfx::Text mouseCoordsText_;

		//info from the other windows useful for status bar output
		int drawWinX_;
		int drawWinY_;
		
	};
}
