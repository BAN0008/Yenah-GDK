#include "Window.hpp"
#include "Config.hpp"
#include "Renderer.hpp"
#include "Log.hpp"
#include "Shader.hpp"
#include "Profiler.hpp"
#include <glad/glad.h>

namespace Yenah
{
	namespace Window
	{
		unsigned char *key_state = nullptr;

		SDL_Window   *window  = nullptr;
		SDL_GLContext context = nullptr;

		FFI_EXPORT unsigned char *GetKeyboardStatePtr()
		{
			return key_state;
		}

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

			key_state = new unsigned char[SDL_NUM_SCANCODES];
			for (unsigned int i = 0; i < SDL_NUM_SCANCODES; i++) {
				key_state[i] = KeyState::UP;
			}

			return true;
		}

		void Destroy()
		{
			delete[] key_state;

			if (context != nullptr) SDL_GL_DeleteContext(context);
			context = nullptr;

			if (window != nullptr) SDL_DestroyWindow(window);
			window = nullptr;
		}

		bool ProcessEvents()
		{
			for (unsigned int i = 0; i < SDL_NUM_SCANCODES; i++) {
				if (key_state[i] == KeyState::PRESSED)  key_state[i] = KeyState::DOWN;
				if (key_state[i] == KeyState::RELEASED) key_state[i] = KeyState::UP;
				if (key_state[i] == KeyState::REPEAT)   key_state[i] = KeyState::DOWN;
			}

			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT:
						return false;
					/*case SDL_KEYDOWN:
						if (event.key.keysym.sym == Config::debug_overlay_toggle_key) {
							Profiler::show_profiler = !Profiler::show_profiler;
						}
						break;*/
					case SDL_KEYDOWN:
						if (event.key.repeat) {
							key_state[event.key.keysym.scancode] = KeyState::REPEAT;
						}
						else {
							key_state[event.key.keysym.scancode] = KeyState::PRESSED;
						}
						break;
					case SDL_KEYUP:
						if (event.key.repeat) {
							key_state[event.key.keysym.scancode] = KeyState::REPEAT;
						}
						else {
							key_state[event.key.keysym.scancode] = KeyState::RELEASED;
						}
					case SDL_WINDOWEVENT:
						if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
							Renderer::ResizeViewport(event.window.data1, event.window.data2);
						}
						break;
				}
			}
			if (key_state[Config::debug_overlay_toggle_key] == KeyState::PRESSED) {
				Profiler::show_profiler = !Profiler::show_profiler;
			}
			return (!Lua::reload);
		}

		void SwapBuffers()
		{
			SDL_GL_SwapWindow(window);
		}
	}
}