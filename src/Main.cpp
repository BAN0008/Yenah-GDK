#include "Window.hpp"
#include "Renderer.hpp"
#include "Log.hpp"
#include "Lua.hpp"
#include <SDL.h>

#ifdef WIN32
	#include <direct.h>
#endif
#ifdef UNIX
	#include <unistd.h>
#endif

using namespace Yenah;

int main(int argc, const char *argv[])
{
	if (argc > 2) {
		printf("Usage: %s [path to game directory]\n", argv[0]);
		return 1;
	}
	if (argc == 2 && chdir(argv[1]) != 0) {
		Log::Fatal("Failed to change directory to %s", argv[1]);
		return 1;
	}

	Lua::Initialize();
	Lua::ReadConfig();

	Window::Create(
		Lua::EngineConfig::window.title, 
		Lua::EngineConfig::window.width,
		Lua::EngineConfig::window.height);

	Renderer::Initialize();

	bool running = true;
	unsigned long previous_time = SDL_GetPerformanceCounter();
	while (running) {
		// Calculate delta time
		unsigned long current_time = SDL_GetPerformanceCounter();
		float delta_time = ((float)(current_time - previous_time) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;
		previous_time = current_time;

		// Process events
		running = Window::ProcessEvents();

		// Draw quads
		for (int x = 0; x < 80; x++) {
			for (int y = 0; y < 45; y++) {
				Renderer::DrawQuad({x * 16.0f, y * 16.0f}, {8.0f, 8.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
			}
		}

		// Render frame
		Renderer::RenderFrame();
		Window::SwapBuffers();
	}

	Renderer::Cleanup();
	Window::Destroy();
	Lua::Cleanup();
	return 0;
}

#ifndef WIN32
	#ifndef UNIX
		#error No compatible platforms defined
	#endif
#endif
