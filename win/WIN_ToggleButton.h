#pragma once
#include "WIN_UIelement.h"
#include <SDL.h>
#include <vector>
#include <memory>

namespace win
{
	class ToggleButton;
	typedef void (*ToggleActionFunction)(ToggleButton* button);
	class ButtonGroup;
	
	class ToggleButton final :
		public UIelement
	{
	public:
		ToggleActionFunction action;
		enum states { off, on };
		
		ToggleButton() = delete;
		ToggleButton(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, ToggleActionFunction act);
		virtual ~ToggleButton();
		ToggleButton(const ToggleButton& that) = default;
		ToggleButton(ToggleButton&& that) = default;
		ToggleButton& operator=(const ToggleButton& that) = default;
		ToggleButton& operator=(ToggleButton&& that) = default;


		void draw() override;
		void mouseEnter() override;
		void mouseExit() override;
		void mouseButtonDown(MouseButton b) override;
		void mouseButtonUp(MouseButton b) override;

		void setButtonGroup(std::shared_ptr<ButtonGroup> buttonGroup);
		void turnOff();
		states getState() const { return state_; }
		void setActivated(bool activated);

	private:
		SDL_Texture* texture_;
		SDL_Renderer* renderer_;
		gfx::Rectangle rect_;
		std::vector<SDL_Rect> spriteClips_;
		SDL_Rect* activeClip_;
		std::shared_ptr<ButtonGroup> buttonGroup_;

		states state_;
		bool activated_;
	};


}
