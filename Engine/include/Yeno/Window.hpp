#pragma once
#include <SDL.h>

namespace Yeno
{
	class Window
	{
	public:
		Window(const char *title, int width, int height);
		~Window();
	private:
		SDL_Window *window = nullptr;
	};
}