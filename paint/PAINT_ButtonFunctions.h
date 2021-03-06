#pragma once

namespace win {
	class SDLRenderer;
	class Button;
	class ToggleButton;
	class UIelement;
}

namespace paint {
	void toggleDraw(win::UIelement* control);
	void toggleDrawRectangle(win::UIelement* control);
	void toggleDrawEllipse(win::UIelement* control);
	void toggleDrawTriangle(win::UIelement* control);
	void setBrushThickness0(win::UIelement* control);
	void setBrushThickness1(win::UIelement* control);
	void setBrushThickness2(win::UIelement* control);
	void swapColours(win::UIelement* control);
	void clearScreen(win::UIelement* control);
	void toggleLock(win::UIelement* control);
	void toggleFill(win::UIelement* control);

}
 