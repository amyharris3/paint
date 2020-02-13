#pragma once
#include "WIN_Window.h"
#include "PAINT_ColourPicker.h"
#include "WIN_ButtonGroup.h"

namespace paint {
	class ToolWindow final :
		public win::Window
	{
	public:
		ToolWindow(const gfx::Rectangle& rect, const char* name, std::shared_ptr<win::Layout> const & layout);
		ToolWindow(const gfx::Rectangle& rect, const char* name);
		virtual ~ToolWindow() = default;
		ToolWindow(const ToolWindow& that) = delete;
		ToolWindow(ToolWindow&& that) = delete;
		ToolWindow& operator=(const ToolWindow& that) = delete;
		ToolWindow& operator=(ToolWindow&& that) = delete;

		void setToolbox(std::shared_ptr<win::Window> toolbox);
		Window* getToolbox() const { return toolbox_.get(); }
		void setColourPicker(std::shared_ptr<ColourPicker> cPick);
		ColourPicker* getColourPicker() const { return colourPicker_.get(); }
		void setThicknessButtonGroup(std::shared_ptr<win::ButtonGroup> buttonGroup) { thicknessButtonGroup_ = buttonGroup; }
		win::ButtonGroup* getThicknessButtonGroup() const { return thicknessButtonGroup_.get(); }
		
		void draw(win::SDLRenderer* renderer) override;
		bool mouseButtonDown(win::MouseButton button, bool clicked = false) override;

	private:

		std::shared_ptr<Window> toolbox_;
		std::shared_ptr <ColourPicker> colourPicker_;
		std::shared_ptr<win::ButtonGroup> thicknessButtonGroup_;
		
	};
}

