#pragma once
#include "Lua.hpp"
#include <SDL.h>

namespace Yenah
{
	namespace Window
	{
		enum KeyState { UP = 0, RELEASED = 1, DOWN = 2, PRESSED = 3, REPEAT = 4 };
		extern unsigned char *key_state;

		extern SDL_Window   *window;
		extern SDL_GLContext context;

		bool Create(const char *title, int width, int height);
		void Destroy();

		FFI_EXPORT bool ProcessEvents(); // Return false if application should quit
		void SwapBuffers();
	};
}