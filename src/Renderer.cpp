#include "Renderer.hpp"
#include "RenderBatch.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Log.hpp"
#include <forward_list>
#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace Yenah
{
	namespace Renderer
	{
		struct Drawable
		{
			Shader *shader;
			int layer;
			unsigned int vertex_count;
			Vertex *vertices;
			Texture *texture;

			Drawable(Shader *shader, int layer, unsigned int vertex_count, Vertex *vertices, Texture *texture) {
				this->shader = shader;
				this->layer = layer;
				this->vertex_count = vertex_count;
				this->vertices = vertices;
				this->texture = texture;
			}

			~Drawable()
			{
				free(vertices);
			}

			static bool Compare(const Drawable &a, const Drawable &b)
			{
				//return (a.layer < b.layer);
				//return false;
				//return (a.texture->GetID() > b.texture->GetID());
				if (!(a.layer < b.layer)) {
					return (a.texture->GetID() > b.texture->GetID());
				}
				return true;
			}
		};

		std::forward_list<Drawable> draw_list;

		bool Initialize()
		{
			if (!gladLoadGL()) {
				Log::Fatal("Failed to initialize OpenGL");
				return false;
			}

			// Check OpenGL version
			int gl_major, gl_minor;
			glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
			glGetIntegerv(GL_MINOR_VERSION, &gl_minor);
			if (gl_major * 10 + gl_minor < 32) {
				Log::Fatal("OpenGL version 3.2 or higher is required");
				Log::Fatal("OpenGL version %d.%d provided", gl_major, gl_minor);
				return false;
			}
			Log::Info("Using OpenGL %s", glGetString(GL_VERSION));

			Shader::Initialize();
			RenderBatch::Initialize();

			SDL_GL_SetSwapInterval(0); // Disable VSYNC
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Initialize imgui
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.IniFilename = nullptr;
			ImGui_ImplSDL2_InitForOpenGL(Window::window, Window::context);
			ImGui_ImplOpenGL3_Init("#version 150 core");
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame(Window::window);
			ImGui::NewFrame();

			return true;
		}

		void Cleanup()
		{
			RenderBatch::Cleanup();
			draw_list.clear();

			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();

			Shader::Cleanup();
		}

		void ResizeViewport(int width, int height)
		{
			glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
			glBindBuffer(GL_UNIFORM_BUFFER, Shader::uniform_buffer);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projection[0][0]);
			glViewport(0, 0, width, height);
		}

		//void DrawQuad(float x, float y, float w, float h, float r, float g, float b, float a, float radians, unsigned int layer, Texture *texture)
		void DrawQuad(float x, float y, float w, float h, float radians, float r, float g, float b, float a, unsigned int layer, void *texture)
		{
			Vertex *vertices = (Vertex *)malloc(sizeof(Vertex) * 6);
			vertices[0] = {x,     y,     0.0f, 1.0f, r, g, b, a};
			vertices[1] = {x + w, y,     1.0f, 1.0f, r, g, b, a};
			vertices[2] = {x + w, y + h, 1.0f, 0.0f, r, g, b, a};

			vertices[3] = {x + w, y + h, 1.0f, 0.0f, r, g, b, a};
			vertices[4] = {x,     y + h, 0.0f, 0.0f, r, g, b, a};
			vertices[5] = {x,     y,     0.0f, 1.0f, r, g, b, a};

			//if (draw_list.empty()) {
				draw_list.emplace_front( Shader::default_shader, layer, 6, vertices, Texture::textures[(unsigned long)texture]);
				return;
			//}
			/*for (auto it = draw_list.begin(); it != draw_list.end(); it++) {
				auto next_it = it;
				next_it++;
				if (layer > (*it).layer || next_it == draw_list.end()) {
					draw_list.emplace_after(it, nullptr, layer, 6, vertices );
					break;
				}
			}*/
			/*if (layer >= layers.size()) {
				for (unsigned int i = layers.size(); i < layer; i++) {
					layers.push_back(nullptr);
				}
				layers.push_back(new RenderBatch());
			}
			else {
				if (layers[layer] == nullptr) layers[layer] = new RenderBatch();
			}

			layers[layer]->AddVertex(position.x, position.y, colour.r, colour.g, colour.b, colour.a);
			layers[layer]->AddVertex(position.x + size.x, position.y, colour.r, colour.g, colour.b, colour.a);
			layers[layer]->AddVertex(position.x + size.x, position.y + size.y, colour.r, colour.g, colour.b, colour.a);

			layers[layer]->AddVertex(position.x + size.x, position.y + size.y, colour.r, colour.g, colour.b, colour.a);
			layers[layer]->AddVertex(position.x, position.y + size.y, colour.r, colour.g, colour.b, colour.a);
			layers[layer]->AddVertex(position.x, position.y, colour.r, colour.g, colour.b, colour.a);*/
		}

		void RenderFrame()
		{
			//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//draw_list.sort(Drawable::Compare);

			// Render draw_list
			if (!draw_list.empty()) {
				Shader *previous_shader = draw_list.front().shader;
				previous_shader->Bind();
				Texture *previous_texture = draw_list.front().texture;
				previous_texture->Bind(); // TODO: Fix
				unsigned int texture_units_used = 0;
				for (auto it = draw_list.begin(); it != draw_list.end(); it++) {
					if (it->shader != previous_shader) {
						RenderBatch::Flush();
						texture_units_used = 0;
						
						previous_shader = it->shader;
						previous_shader->Bind();
					}
					if (it->texture != previous_texture) {
						if (++texture_units_used > GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
							RenderBatch::Flush();
							texture_units_used = 0;
						}

						previous_texture = it->texture;
					}

					// Add to RenderBatch
					for (unsigned int i = 0; i < it->vertex_count; i++) {
						RenderBatch::AddVertex(it->vertices + i);
					}
				}
				RenderBatch::Flush();
				texture_units_used = 0;
			}

			draw_list.clear();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame(Window::window);
			ImGui::NewFrame();
			Window::SwapBuffers();
		}

		void SetVSync(bool enabled)
		{
			SDL_GL_SetSwapInterval(enabled);
		}

		bool GetVSync()
		{
			return (SDL_GL_GetSwapInterval() != 0);
		}
	}
}