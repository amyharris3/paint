#pragma once
#include "WIN_UIelement.h"
#include "GFX_Renderer.h"

namespace gfx {
	class Renderer;
}

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

namespace win
{

	class Button;
	
	class Button final:
		public UIelement
	{
	public:
		Button() = delete;
		Button(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, ActionFunction act);
		virtual ~Button();
		Button(const Button& that) = default;
		Button(Button&& that) = default;
		Button& operator=(const Button& that) = default;
		Button& operator=(Button&& that) = default;

		void draw() override;
		bool mouseEnter() override;
		bool mouseExit() override;
		bool mouseButtonDown(MouseButton b) override;
		bool mouseButtonUp(MouseButton b) override;

		ActionFunction action;

	private:
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		gfx::Rectangle rect_;
		std::vector<SDL_Rect> spriteClips_;
		SDL_Rect* activeClip_;
	};
}
