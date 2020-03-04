#include <Yeno/Window.hpp>
#include <Yeno/Log.hpp>
#include "Config.hpp"
#include <glad/glad.h>

namespace Yeno
{
	Window::Window(const char *title, int width, int height)
	{
		SDL_ClearError();
		window = SDL_CreateWindow(title,
		                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		                          width, height,
		                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (window == nullptr) {
			Log::Fatal("Fatal Error: Failed to create window: %s\n", SDL_GetError());
			return;
		}

		SDL_ClearError();
		context = SDL_GL_CreateContext(window);
		if (context == nullptr) {
			Log::Fatal("Fatal Error: Failed to create OpenGL context: %s\n", SDL_GetError());
			return;
		}

		if (!gladLoadGL()) {
			Log::Fatal("Fatal Error: Failed to initialize OpenGL\n");
			return;
		}
		Log::Info("Info: Using OpenGL %s\n", glGetString(GL_VERSION));

		GLint gl_major, gl_minor;
		glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
		glGetIntegerv(GL_MAJOR_VERSION, &gl_minor);

		if (gl_major >= 4 && gl_minor >= 4) {
			Config::use_persistent_mapping = true;
		}
		else {
			Config::use_persistent_mapping = false;
			Log::Warn("Warning: Driver doesn't support persistent buffer mapping\n");
		}
	}
	Window::~Window()
	{
		if (context != nullptr) SDL_GL_DeleteContext(context);
		if (window != nullptr) SDL_DestroyWindow(window);
		window = nullptr;
	}

	void Window::ProcessEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					if (window != nullptr) SDL_DestroyWindow(window);
					window = nullptr;
					break;
			}
		}
	}

	bool Window::IsOpen()
	{
		return (window != nullptr);
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SwapBuffer()
	{
		SDL_GL_SwapWindow(window);
	}
}