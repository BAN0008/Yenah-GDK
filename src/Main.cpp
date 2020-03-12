#include "Window.hpp"
#include "Renderer.hpp"
#include "Lua.hpp"

using namespace Yenah;

int main(int argc, const char *argv[])
{
	Lua::Initialize();
	Window::Create(
			Lua::EngineConfig::window.title, 
			Lua::EngineConfig::window.width,
			Lua::EngineConfig::window.height);
	Renderer::Initialize();
	Renderer::Cleanup();
	Window::Destroy();
	Lua::Cleanup();
	return 0;
}

#ifndef WIN32
	#ifndef UNIX
		#error No compaitible platforms defined
	#endif
#endif
