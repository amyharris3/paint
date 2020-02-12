#pragma once
#include "WIN_UIelement.h"

namespace gfx {
	class Renderer;
}

namespace win
{
	class SDLRenderer;
	class ToggleButton;
	class ButtonGroup;
	enum class ButtonStates;
	
	class ToggleButton final :
		public UIelement
	{
	public:
		ActionFunction action;
		enum states { off, on };
		
		ToggleButton() = delete;
		ToggleButton(win::SDLRenderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, ActionFunction act);
		virtual ~ToggleButton();
		ToggleButton(const ToggleButton& that) = default;
		ToggleButton(ToggleButton&& that) = default;
		ToggleButton& operator=(const ToggleButton& that) = default;
		ToggleButton& operator=(ToggleButton&& that) = default;
	
		void draw(win::SDLRenderer* renderer) override;
		bool mouseEnter(bool clicked = false) override;
		bool mouseExit(bool clicked = false) override;
		bool mouseMove(SDL_MouseMotionEvent& e) override	;
		bool mouseButtonDown(MouseButton b) override;
		bool mouseButtonUp(MouseButton b, win::SDLRenderer* renderer = nullptr) override;

		void setButtonGroup(std::shared_ptr<ButtonGroup> buttonGroup);
		void turnOff();
		ButtonStates getState() const { return state_; }
		void setActivated(bool activated);

	private:
		win::SDLRenderer* renderer_;
		SDL_Texture* texture_;
		//SDL_Renderer* renderer_;
		
		gfx::Rectangle rect_;
		std::vector<SDL_Rect> spriteClips_;
		SDL_Rect* activeClip_;
		std::shared_ptr<ButtonGroup> buttonGroup_;

		ButtonStates state_;
		bool activated_;

		bool mouseDown_;
		bool mouseDragged_;
	};


}
