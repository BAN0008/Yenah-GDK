#pragma once
#include <glm/glm.hpp>

namespace Yeno
{
	namespace Camera
	{
		void SetPosition(glm::vec2 position);
		void SetRotation(float radians);
		void SetSize(glm::vec2 size);
		void SetScale(glm::vec2 scale);
	}
}