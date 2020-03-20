#pragma once
#include <SDL.h>
#define FFI_EXPORT extern "C" __attribute__ ((visibility ("default")))

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