#pragma once
#include <SDL.h>

namespace Yenah
{
	namespace Window
	{
		extern SDL_Window   *window;
		extern SDL_GLContext context;

		bool Create(const char *title, int width, int height);
		void Destroy();

		bool ProcessEvents(); // Return false if application should quit
		void SwapBuffers();
	};
}