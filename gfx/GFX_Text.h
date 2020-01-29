#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

// Handling text loading and rendering
namespace gfx
{
	class Text
	{
	public:
		Text() = delete;
		Text(const char* textString);
		~Text() = default;
		Text(const Text & that) = default;
		Text(Text && that) = default;
		Text& operator=(const Text & that) = default;
		Text& operator=(Text && that) = default;

	private:

		std::string textString_;
		
	};
}
