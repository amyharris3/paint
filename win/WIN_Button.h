#pragma once
#include "WIN_UIelement.h"
#include <string>

struct SDL_Texture;
struct SDL_Renderer;


namespace win
{
	//enum class ButtonState
	//{
	//	BUTTON_SPRITE_MOUSE_OUT,
	//	BUTTON_SPRITE_MOUSE_OVER,
	//	BUTTON_SPRITE_MOUSE_DOWN,
	//	BUTTON_SPRITE_MOUSE_UP,
	//};

	class Button :
		public UIelement
	{
	public:
		Button() = default;
		Button(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name);
		virtual ~Button();
		Button(const Button& that) = default;
		Button(Button&& that) = default;
		Button& operator=(const Button& that) = default;
		Button& operator=(Button&& that) = default;

		void draw() override;
		void mouseEnter() override;
		void mouseExit() override;
		void mouseButtonDown(MouseButton b, int xPixel, int yPixel) override;
		void mouseButtonUp(MouseButton button) override;

		SDL_Texture* loadSprite(const char* path);

	private:
		//ButtonState buttonState_;
		SDL_Texture* texture_;
		SDL_Renderer* renderer_;
		gfx::Rectangle rect_;
	};
}
