#pragma once
#include "Lua.hpp"
#include <SDL.h>

namespace Yenah
{
	namespace Window
	{
		extern SDL_Window   *window;
		extern SDL_GLContext context;

		bool Create(const char *title, int width, int height);
		void Destroy();

		FFI_EXPORT bool ProcessEvents(); // Return false if application should quit
		void SwapBuffers();
	};
}