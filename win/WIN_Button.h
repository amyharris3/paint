#pragma once
#include "WIN_UIelement.h"
#include <SDL.h>
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

namespace win
{

	class Button;
	typedef void (*ActionFunction)(Button * button);
	
	class Button final:
		public UIelement
	{
	public:
		Button() = delete;
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
		SDL_Texture* texture_;
		SDL_Renderer* renderer_;
		gfx::Rectangle rect_;
		std::vector<SDL_Rect> spriteClips_;
		SDL_Rect* activeClip_;
		bool clicked_;
	};
}
