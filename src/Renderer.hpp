#pragma once
#include "Lua.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>

namespace Yenah
{
	namespace Renderer
	{
		bool Initialize();
		void Cleanup();
		//void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 colour, float radians = 0.0f, unsigned int layer = 0, Texture *texture = nullptr);
		void DrawQuad(float x, float y, float w, float h, float r, float g, float b, float a, float radians = 0.0f, unsigned int layer = 0, Texture *texture = nullptr);
		FFI_EXPORT void RenderFrame();
		void SetVSync(bool enabled);
		bool GetVSync();
	}
}