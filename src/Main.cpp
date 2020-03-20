#include "Window.hpp"
#include "Renderer.hpp"
#include "Log.hpp"
#include "Lua.hpp"
#include "Config.hpp"
#include "Texture.hpp"
#include <SDL.h>
#include <imgui.h>

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
		Config::window_title, 
		Config::window_width,
		Config::window_height);

	Renderer::Initialize();

	Lua::Start();

	/*Texture *texture1 = new Texture("res/test.png");
	Texture *texture2 = new Texture("res/clover.png");

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
		for (int x = 0; x < (1920 / 128) + 1; x++) {
			for (int y = 0; y < (1080 / 64) + 1; y++) {
				Renderer::DrawQuad({x * 128.0f, y * 64.0f}, {64.0f, 64.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, 0.0f, 0, texture1);
				Renderer::DrawQuad({(x * 128.0f) + 64.0f, y * 64.0f}, {64.0f, 64.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, 0.0f, 0, texture2);
			}
		}

		ImGui::Begin("Profiler");
		ImGui::Text("dt: %f", delta_time);
		bool vsync = Renderer::GetVSync();
		ImGui::Checkbox("VSYNC", &vsync);
		Renderer::SetVSync(vsync);
		ImGui::End();

		// Render frame
		Renderer::RenderFrame();
		Window::SwapBuffers();
	}

	delete texture1;
	delete texture2;*/

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