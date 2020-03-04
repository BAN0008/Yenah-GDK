#include <Yeno/Window.hpp>

using namespace Yeno;

int main(int argc, char **argv)
{
	Window *window = new Window("TestApp", 1280, 720);
	delete window;
	return 0;
}