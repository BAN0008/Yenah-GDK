#include "Window.hpp"
#include "Renderer.hpp"

using namespace Yenah;

int main(int argc, const char *argv[])
{
	// TODO: Run config.lua to get parameters for Window::Create()
	Window::Create("Test", 1280, 720);
	Renderer::Initialize();
	Renderer::Cleanup();
	Window::Destroy();
	return 0;
}

#ifndef WIN32
	#ifndef UNIX
		#error No compaitible platforms defined
	#endif
#endif