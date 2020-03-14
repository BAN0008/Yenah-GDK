#include "Window.hpp"
#include "Renderer.hpp"
#include "Log.hpp"
#include "Lua.hpp"

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

	// Start up LuaJit and read the engine config
	Lua::Initialize();
	Lua::ReadConfig();

	Window::Create(
		Lua::EngineConfig::window.title, 
		Lua::EngineConfig::window.width,
		Lua::EngineConfig::window.height);

	Renderer::Initialize();
	Lua::Start();

	while (true) {
		//Window::ProcessEvents();
		Lua::UpdateObjects(69.0);
		//Window::SwapBuffers();
		Lua::DrawObjects();
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