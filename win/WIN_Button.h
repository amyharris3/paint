#pragma once
#include "WIN_UIelement.h"
#include <string>
#include <SDL.h>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;


namespace win
{
	enum class ButtonState
	{
		BUTTON_SPRITE_MOUSE_OUT,
		BUTTON_SPRITE_MOUSE_OVER,
		BUTTON_SPRITE_MOUSE_DOWN,
		BUTTON_SPRITE_MOUSE_UP,
	};

	class Button;
	typedef void (*ActionFunction)(Button * button);

	class Button :
		public UIelement
	{
	public:
		Button() = default;
		Button(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, ActionFunction act);
		virtual ~Button();
		Button(const Button& that) = default;
		Button(Button&& that) = default;
		Button& operator=(const Button& that) = default;
		Button& operator=(Button&& that) = default;

		void draw() override;
		void mouseEnter() override;
		void mouseExit() override;
		void mouseButtonDown(MouseButton b) override;
		void mouseButtonUp(MouseButton b) override;

		ActionFunction action;

	private:
		ButtonState buttonState_;
		SDL_Texture* texture_;
		SDL_Renderer* renderer_;
		gfx::Rectangle rect_;
		SDL_Rect spriteClips_[4];
		SDL_Rect* activeClip_;
		SDL_Rect buttonRect_;
		bool clicked_;

		SDL_Texture* loadSprite(const char* path);
		void handleSpriteSheet();
	};
}
