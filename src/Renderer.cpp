#include "Renderer.hpp"
#include "RenderBatch.hpp"
#include "Shader.hpp"
#include "Log.hpp"
#include <vector>
#include <SDL.h>

#include <glad/glad.h>

// TODO: Make new RenderBatch when old one is full

namespace Yenah
{
	namespace Renderer
	{
		std::vector<RenderBatch *> layers;

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
			return true;
		}

		void Cleanup()
		{
			for (unsigned int i = 0; i < layers.size(); i++) {
				delete layers[i];
				layers[i] = nullptr;
			}
			layers.clear();

			Shader::Cleanup();
		}

		void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 colour, float radians, unsigned int layer, Texture *texture)
		{
			if (layer >= layers.size()) {
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
			layers[layer]->AddVertex(position.x, position.y, colour.r, colour.g, colour.b, colour.a);
		}

		void RenderFrame()
		{
			glClear(GL_COLOR_BUFFER_BIT);
			for (unsigned int i = 0; i < layers.size(); i++) {
				layers[i]->Render();
				layers[i]->Clear();
			}
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