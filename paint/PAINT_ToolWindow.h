#pragma once
#include "WIN_Window.h"
#include "PAINT_ColourPicker.h"

namespace paint {
	class ToolWindow final :
		public win::Window
	{
	public:
		ToolWindow(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name, std::shared_ptr<win::Layout> const & layout);
		ToolWindow(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name);
		virtual ~ToolWindow() = default;
		ToolWindow(const ToolWindow& that) = delete;
		ToolWindow(ToolWindow&& that) = delete;
		ToolWindow& operator=(const ToolWindow& that) = delete;
		ToolWindow& operator=(ToolWindow&& that) = delete;

		void setToolbox(std::shared_ptr<win::Window> toolbox);
		Window* getToolbox() const { return toolbox_.get(); }
		void setColourPicker(std::shared_ptr<ColourPicker> cPick);
		ColourPicker* getColourPicker() const { return colourPicker_.get(); }
		
		void draw() override;
		bool mouseButtonDown(win::MouseButton button, bool clicked) override;

	private:

		std::shared_ptr<Window> toolbox_;
		std::shared_ptr <ColourPicker> colourPicker_;
		
	};
}

