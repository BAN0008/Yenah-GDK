#pragma once
#include <glm.hpp>

namespace Yeno
{
	namespace Camera
	{
		void SetPosition(glm::vec2 position);
		void SetRotation(float radians);
		void SetScale(glm::vec2 scale);
	}
}