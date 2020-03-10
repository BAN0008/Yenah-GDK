#include <Yeno/Window.hpp>
#include <Yeno/Shader.hpp>
#include <Yeno/Camera.hpp>
#include <Yeno/Config.hpp>
#include <Yeno/Scripting.hpp>

#include "../../Engine/src/RenderBatch.hpp"
#include "../../Engine/vendor/imgui/include/imgui.h"

#include <vector>
#include <iostream>

using namespace Yeno;

int main(int argc, char **argv)
{
	Window *window = new Window("TestApp", 1280, 720);
	RenderBatch *batch = new RenderBatch();
	Scripting::Initialize();

	auto previous_time = SDL_GetPerformanceCounter();
	while (window->IsOpen()) {
		auto current_time = SDL_GetPerformanceCounter();
		float delta_time = ((float)(current_time - previous_time) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;
		previous_time = current_time;

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
			scale -= 0.001f;
			if (scale <= 0.0f) {
				scale += 0.001f;
				scale_down = false;
			}
		}
		else {
			scale += 0.001f;
			if (scale >= 2.0f) {
				scale -= 0.001f;
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

		for (int i = 0; i < 100; i++) {
			y_pos += 128.0f;
			for (int j = 0; j < 100; j++) {
				x_pos += 128.0f;
				batch->AddVertex(x_pos + 0.0f,  y_pos + 0.0f,  1.0f, 0.0f, 0.0f, 1.0f);
				batch->AddVertex(x_pos + 0.0f,  y_pos + 64.0f, 0.0f, 1.0f, 0.0f, 1.0f);
				batch->AddVertex(x_pos + 64.0f, y_pos + 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);
				batch->AddVertex(x_pos + 0.0f,  y_pos + 0.0f,  1.0f, 0.0f, 0.0f, 1.0f);
				batch->AddVertex(x_pos + 64.0f, y_pos + 0.0f,  1.0f, 1.0f, 0.0f, 1.0f);
				batch->AddVertex(x_pos + 64.0f, y_pos + 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			}
			x_pos -= 128.0f * 100;
		}

		batch->AddVertex((1280.0f / 2.0f) - 4.0f, (720.0f / 2.0f) - 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) + 4.0f, (720.0f / 2.0f) - 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) + 4.0f, (720.0f / 2.0f) + 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) - 4.0f, (720.0f / 2.0f) - 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) - 4.0f, (720.0f / 2.0f) + 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		batch->AddVertex((1280.0f / 2.0f) + 4.0f, (720.0f / 2.0f) + 4.0f, 0.0f, 1.0f, 0.0f, 1.0f);

		ImGui::Begin("Profiler");
		//ImGui::Checkbox("V-SYNC", &Config::vsync);
		bool vsync = Config::GetVSync();
		ImGui::Checkbox("V-SYNC", &vsync);
		Config::SetVSync(vsync);
		//ImGui::Checkbox("Anti-aliasing", &Config::antialiasing);
		bool antialiasing = Config::GetAntialiasing();
		ImGui::Checkbox("Anti-aliasing", &antialiasing);
		Config::SetAntialiasing(antialiasing);

		//Frame rate counter
		static std::vector<float> delta_times;
		delta_times.insert((delta_times.begin() + delta_times.size()), delta_time);
		if (delta_times.size() > 500) {
			delta_times.erase(delta_times.begin());
		}
		//ImGui::PlotLines(label, values, value_count, offset, overlay_text, scale_min, scale_max, graphsize, stride);
		ImGui::PlotLines("Deltatime", delta_times.data(), delta_times.size(), 0, "(ms)", 0.0f, 33.2f, {256, 64});

		ImGui::End();

		batch->Render();
		window->SwapBuffer();
	}
	delete batch;
	delete window;
	return 0;
}