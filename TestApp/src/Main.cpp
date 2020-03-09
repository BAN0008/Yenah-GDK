#include <Yeno/Window.hpp>
#include <Yeno/Shader.hpp>
#include <Yeno/Camera.hpp>
#include <Yeno/Scripting.hpp>
#include "../../Engine/src/RenderBatch.hpp"

using namespace Yeno;

int main(int argc, char **argv)
{
	Window *window = new Window("TestApp", 1280, 720);
	RenderBatch *batch = new RenderBatch();
	Scripting::Initialize();
	while (window->IsOpen()) {
		window->ProcessEvents();
		window->Clear();

		//Test rotation
		static float rotation = 0.0f;
		rotation++;
		if (rotation > 360.0f) rotation -= 360.0f;
		Camera::SetRotation(rotation * (3.14f / 180.0f));

		//Test scale
		static float scale = 1.0f;
		static bool scale_down = true;
		if (scale_down) {
			scale -= 0.05f;
			if (scale <= 0.0f) {
				scale += 0.05f;
				scale_down = false;
			}
		}
		else {
			scale += 0.05f;
			if (scale >= 2.0f) {
				scale -= 0.05f;
				scale_down = true;
			}
		}
		Camera::SetScale({scale, scale});

		//Render quads
		batch->Clear();
		float x_pos = (1280.0f / 2.0f) - (192.0f / 2.0f);
		float y_pos = (720.0f  / 2.0f) - 32.0f;
		batch->AddVertex(x_pos + 0.0f,  y_pos + 0.0f,  1.0f, 0.0f, 0.0f, 1.0f);
		batch->AddVertex(x_pos + 0.0f,  y_pos + 64.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex(x_pos + 64.0f, y_pos + 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		batch->AddVertex(x_pos + 0.0f,  y_pos + 0.0f,  1.0f, 0.0f, 0.0f, 1.0f);
		batch->AddVertex(x_pos + 64.0f, y_pos + 0.0f,  1.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex(x_pos + 64.0f, y_pos + 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		x_pos += 128.0f;

		batch->AddVertex(x_pos + 0.0f,  y_pos + 0.0f,  1.0f, 0.0f, 0.0f, 1.0f);
		batch->AddVertex(x_pos + 0.0f,  y_pos + 64.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex(x_pos + 64.0f, y_pos + 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		batch->AddVertex(x_pos + 0.0f,  y_pos + 0.0f,  1.0f, 0.0f, 0.0f, 1.0f);
		batch->AddVertex(x_pos + 64.0f, y_pos + 0.0f,  1.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex(x_pos + 64.0f, y_pos + 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		batch->AddVertex((1280.0f / 2.0f) - 4.0f, (720.0f / 2.0f) - 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) + 4.0f, (720.0f / 2.0f) - 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) + 4.0f, (720.0f / 2.0f) + 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) - 4.0f, (720.0f / 2.0f) - 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) - 4.0f, (720.0f / 2.0f) + 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) + 4.0f, (720.0f / 2.0f) + 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);

		batch->Render();
		window->SwapBuffer();
	}
	delete batch;
	delete window;
	return 0;
}