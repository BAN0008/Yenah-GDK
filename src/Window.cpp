#include "Window.hpp"
#include "Config.hpp"
#include "Renderer.hpp"
#include "Log.hpp"
#include "Shader.hpp"
#include <glad/glad.h>

namespace Yenah
{
	namespace Window
	{
		SDL_Window   *window  = nullptr;
		SDL_GLContext context = nullptr;

		bool Create(const char *title, int width, int height)
		{
			SDL_ClearError();
			window = SDL_CreateWindow(title,
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				width, height,
				SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

			if (window == nullptr) {
				Log::Fatal("Failed to create window: %s", SDL_GetError());
				return false;
			}

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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

			if (window != nullptr) SDL_DestroyWindow(window);
			window = nullptr;
		}

		bool ProcessEvents()
		{
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT:
						return false;
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == Config::debug_overlay_toggle_key) {
							// TODO: Toggle debug overlay
						}
						break;
					case SDL_WINDOWEVENT:
						if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
							Renderer::ResizeViewport(event.window.data1, event.window.data2);
						}
						break;
				}
			}
			return true;
		}

		void SwapBuffers()
		{
			SDL_GL_SwapWindow(window);
		}
	}
}