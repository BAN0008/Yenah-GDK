#include <SDL.h>
#include "Log.hpp"

namespace Yenah
{
	namespace Window
	{
		SDL_Window   *window  = nullptr;
		SDL_GLContext context = nullptr;

		bool Create(const char *title, int width, int height)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_ClearError();
			window = SDL_CreateWindow(title,
			                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			                          width, height,
			                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
			if (window == nullptr) {
				Log::Fatal("Failed to create window: %s", SDL_GetError());
				return false;
			}

			SDL_ClearError();
			context = SDL_GL_CreateContext(window);
			if (context == nullptr) {
				Log::Fatal("Failed to create OpenGL context: %s", SDL_GetError());
				return false;
			}
			SDL_GL_MakeCurrent(window, context);

			return true;
		}

		void Destroy()
		{
			if (context != nullptr) SDL_GL_DeleteContext(context);
			context = nullptr;

			if (window == nullptr) SDL_DestroyWindow(window);
			window = nullptr;
		}
	}
}