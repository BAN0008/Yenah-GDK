#include <Yeno/Camera.hpp>
#include <Yeno/Shader.hpp>
#include <gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace Yeno
{
	glm::vec2 position(0.0f, 0.0f);
	float rotation = 0.0f; //Rotation in radians
	glm::vec2 scale(1.0f, 1.0f);

	void UpdateMatrix()
	{
		glm::mat4 view(1.0f);
		view = glm::translate(view, {1280.0f / 2.0f, 720.0f / 2.0f, 0.0f});
		view = glm::rotate(view, rotation, {0.0f, 0.0f, 1.0f});
		view = glm::translate(view, {1280.0f / -2.0f, 720.0f / -2.0f, 0.0f});
		view = glm::translate(view, {position.x, position.y, 0.0f});
		view = glm::scale(view, {scale.x, scale.y, 1.0f});
		glBindBuffer(GL_UNIFORM_BUFFER, Shader::uniform_buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &view[0][0]);
	}

	void Camera::SetPosition(glm::vec2 position)
	{
		::Yeno::position = position;
		UpdateMatrix();
	}
	
	void Camera::SetRotation(float radians)
	{
		rotation = radians;
		UpdateMatrix();
	}
	
	void Camera::SetScale(glm::vec2 scale)
	{
		::Yeno::scale = scale;
		UpdateMatrix();
	}
}