#pragma once
#include "WIN_Button.h"

namespace win {
	class Button;
}

namespace paint {

	void myAction(win::Button* button);

	//void foo();

	void toggleDraw(win::Button* button);
	void swapColours(win::Button* button);
	void clearScreen(win::Button* button);
}

 