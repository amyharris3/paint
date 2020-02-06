#pragma once

namespace win {
	class Button;
	class ToggleButton;
	class UIelement;
}

namespace paint {

	void toggleDraw(win::UIelement* control);
	static void setBrushThickness(win::UIelement* control, int thick);
	void setBrushThickness0(win::UIelement* control);
	void setBrushThickness1(win::UIelement* control);
	void setBrushThickness2(win::UIelement* control);
	void swapColours(win::UIelement* control);
	void clearScreen(win::UIelement* control);
}

 