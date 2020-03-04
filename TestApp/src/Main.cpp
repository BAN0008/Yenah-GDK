#include <Yeno/Window.hpp>
#include <Yeno/Shader.hpp>
#include "/home/brad/Documents/Yeno-GDK/Engine/src/RenderBatch.hpp"

using namespace Yeno;

int main(int argc, char **argv)
{
	Window *window = new Window("TestApp", 1280, 720);
	Shader::CreateDefaultShader();
	RenderBatch *batch = new RenderBatch();
	batch->AddVertex(-0.5f, -0.5f);
	batch->AddVertex(0.5f, -0.5f);
	batch->AddVertex(0.5f, 0.5f);
	while (window->IsOpen()) {
		window->ProcessEvents();
		window->Clear();
		batch->Render();
		window->SwapBuffer();
	}
	delete batch;
	delete window;
	return 0;
}