#include <Yeno/Window.hpp>

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
			//TODO: Log error message
		}
	}
	Window::~Window()
	{
		SDL_DestroyWindow(window);
	}
}