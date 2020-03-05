#include <Yeno/Window.hpp>
#include <Yeno/Shader.hpp>
#include "../../Engine/src/RenderBatch.hpp"

using namespace Yeno;

int main(int argc, char **argv)
{
	Window *window = new Window("TestApp", 1280, 720);
	Shader::Initialize();
	Shader::CreateDefaultShader();
	RenderBatch *batch = new RenderBatch();
	batch->AddVertex(64.0f, 64.0f);
	batch->AddVertex(64.0f, 128.0f);
	batch->AddVertex(128.0f, 128.0f);
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