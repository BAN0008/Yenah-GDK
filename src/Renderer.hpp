#pragma once
#include <glm/glm.hpp>

namespace Yenah
{
	typedef void Texture; // TODO: Create texture class
	namespace Renderer
	{
		bool Initialize();
		void Cleanup();
		void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 colour, float radians = 0.0f, unsigned int layer = 0, Texture *texture = nullptr);
		void RenderFrame();
		void SetVSync(bool enabled);
		bool GetVSync();
	}
}