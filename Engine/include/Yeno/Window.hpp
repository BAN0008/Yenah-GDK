#pragma once
#include <SDL.h>

namespace Yeno
{
	class Window
	{
	public:
		Window(const char *title, int width, int height);
		~Window();

		void ProcessEvents();
		bool IsOpen();

		void Clear();
		void SwapBuffer();
	private:
		SDL_Window *window = nullptr;
		SDL_GLContext context = nullptr;
		bool open = true;
	};
}