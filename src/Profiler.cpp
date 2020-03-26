#include "Profiler.hpp"
#include "Renderer.hpp"
#include <list>
#include <string>
#include <imgui.h>
#include <SDL.h>

namespace Yenah
{
	namespace Profiler
	{
		struct FrameInfo
		{
			float time; // Frame time

			// Breakdown of frame time
			float time_breakdown[10];
			std::string breakdown_descriptions[10];
			unsigned int breakdown_count;

			unsigned int draw_calls;   // Number of draw calls
			unsigned int vertices;     // Number of vertices
			unsigned int textures;     // Number of texture units
			unsigned int game_objects; // Number of game objects updated
		};

		bool profile = true, pause = false, advance_frame = false;

		//FrameInfo *frames = nullptr;
		std::list<FrameInfo> frames;
		unsigned int frame_count = 0;

		unsigned long long start_time = 0;
		unsigned long long previous_time = 0;

		float highest_time = -1.0f, lowest_time = -1.0f;

		FrameInfo frame;

		void BeginFrame()
		{
			start_time = SDL_GetPerformanceCounter();
			previous_time = start_time;
			frame.breakdown_count = 0;
			frame.draw_calls   = 0;
			frame.vertices     = 0;
			frame.textures     = 0;
			frame.game_objects = 0;
		}

		void Time(const char *description)
		{
			frame.breakdown_descriptions[frame.breakdown_count] = std::string(description);
			const auto current_time = SDL_GetPerformanceCounter();
			frame.time_breakdown[frame.breakdown_count] = ((float)(current_time - previous_time) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;
			previous_time = current_time;
			frame.breakdown_count++;
		}

		void SetDrawCalls(unsigned int number)
		{
			frame.draw_calls = number;
		}

		void SetVertices(unsigned int number)
		{
			frame.vertices = number;
		}

		void SetTextures(unsigned int number)
		{
			frame.textures = number;
		}

		bool EndFrame()
		{
			Profiler::Time("End frame");
			float time = ((float)(SDL_GetPerformanceCounter() - start_time) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;
			frame.time = time;

			if (profile) {
				if (time > highest_time || highest_time < 0.0f) highest_time = time;
				if (lowest_time > time  || lowest_time < 0.0f)  lowest_time = time;

				frames.push_back(frame);
				if (frames.size() > 60) frames.pop_front();
			}
			if (advance_frame) {
				advance_frame = false;
				profile = false;
				pause = true;
			}
			return pause;
		}

		void Show()
		{
			ImGui::Begin("Profiler");

			ImGui::Checkbox("Pause", &pause);
			if (ImGui::Button("Advance Frame")) {
				pause = false;
				advance_frame = true;
			}
			profile = !pause;

			ImGui::Text("Frame Time / FPS: %f / %f", frames.back().time, 1000.0f / frames.back().time);
			ImGui::Text("Highest Frame Time / Lowest FPS: %f / %f", highest_time, 1000.0f / highest_time);
			ImGui::Text("Lowest Frame Time / Highest FPS: %f / %f", lowest_time,  1000.0f / lowest_time);
			if (ImGui::Button("Reset")) {
				lowest_time  = -1.0f;
				highest_time = -1.0f;
			}

			//float times[frames.size()];
			float *times = new float[frames.size()];
			int i = 0;
			for (auto it = frames.begin(); it != frames.end(); it++) {
				times[i++] = it->time;
			}
			ImGui::PlotHistogram("Frame Time", times, frames.size(), 0, nullptr, 0.0f, 33.1f);
			delete times;

			bool vsync = Renderer::GetVSync();
			ImGui::Checkbox("VSYNC", &vsync);
			Renderer::SetVSync(vsync);

			// Draw time breakdown
			if (!frames.empty()) {
				auto imgui_draw_list = ImGui::GetWindowDrawList();
				float x = ImGui::GetCursorScreenPos().x;
				float y = ImGui::GetCursorScreenPos().y;
				float width = 256.0f;
				float height = (frames.back().breakdown_count * 16.0f) + 24.0f;
				imgui_draw_list->AddRectFilled({x, y}, {x + width, y + height}, ImGui::GetColorU32(ImGuiCol_FrameBg));
				float offset = 0;
				const ImU32 colours[] = {0xff0000ff, 0xff00ff00, 0xffff0000, 0xff00ffff, 0xffffffff, 0xffff00ff, 0xffffff00, 0xffffffff, 0xffff0000, 0xffffffff, 0xffff0000, 0xffffffff};
				//FrameInfo frame2 = frames.back(); // TODO: Delete this line
				for (int i = 0; i < frames.back().breakdown_count; i++) {
					float time_width = (width / frames.back().time) * frames.back().time_breakdown[i];
					imgui_draw_list->AddRectFilled({x + offset, y}, {x + offset + time_width, y + 16.0f}, colours[i]);
					//char *buffer = (char *)malloc(2048);
					//snprintf(buffer, 2046,"%s (%f)", frames.back().breakdown_descriptions[i], frames.back().time_breakdown[i]);
					imgui_draw_list->AddText({x, y + ((i + 1) * 16.0f)}, colours[i],
						(frames.back().breakdown_descriptions[i] +
						std::string("(") +
						std::to_string(frames.back().time_breakdown[i]) +
						std::string(")")).c_str());
					//free(buffer);
					offset += time_width;
				}
				ImGui::SetCursorScreenPos({x, y + height});
				/*imgui_draw_list->AddRectFilled({x, y}, {x + 192.0f, y + 32.0f}, ImGui::GetColorU32(ImGuiCol_FrameBg));
				for (int i = 0; i < 16; i++) {
					imgui_draw_list->AddLine({x + (i * 12), y}, {x + (i * 12), y + 4}, ImGui::GetColorU32(ImGuiCol_Text));
				}
				imgui_draw_list->AddText({x, y}, ImGui::GetColorU32(ImGuiCol_Text), std::to_string(10).c_str());
				ImGui::SetCursorScreenPos({x, y + 32.0f});*/
			}


			ImGui::Text("Draw Calls: %u", frames.back().draw_calls);
			ImGui::Text("Vertices: %u", frames.back().vertices);
			ImGui::Text("Texture Changes: %u", frames.back().textures);
			ImGui::Text("Game Objects: %u", frames.back().game_objects);

			ImGui::End();
		}
	}
}