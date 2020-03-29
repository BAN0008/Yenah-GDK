#include "Camera.hpp"
#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Yenah
{
	namespace Camera
	{
		void UpdateCamera(float x, float y, float scale_x, float scale_y, float radians, float origin_x, float origin_y)
		{
			glm::mat4 view(1.0f);
			view = glm::translate(view, {x, y, 0.0f});
			view = glm::translate(view, {origin_x, origin_y, 0.0f});
			view = glm::scale(view, {scale_x, scale_y, 1.0f});
			view = glm::rotate(view, radians, {0.0f, 0.0f, 1.0f});
			view = glm::translate(view, {-origin_x, -origin_y, 0.0f});
			glBindBuffer(GL_UNIFORM_BUFFER, Shader::uniform_buffer);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &view[0][0]);
		}
	}
}