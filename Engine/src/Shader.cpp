#include <Yeno/Shader.hpp>

namespace Yeno
{
	Shader::Shader()
	{
		program_id = glCreateProgram();
	}
	Shader::~Shader()
	{
		glDeleteProgram(program_id);
	}

	Shader *Shader::CreateFromStrings(const char *vertex_code, const char *fragment_code, const char *geometry_code)
	{
		Shader *new_shader = new Shader();
		GLint success;
		GLchar info_log[4096];

		GLuint vertex_id = glCreateProgram(GL_VERTEX_SHADER);
		glShaderSource(vertex_id, 1, &vertex_code, nullptr);
		glCompileShader(vertex_id);
		glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex_id, 4096, nullptr, info_log);
			//TODO: Log error
		}

		GLuint fragment_id = glCreateProgram(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_id, 1, &fragment_code, nullptr);
		glCompileShader(fragment_id);
		glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment_id, 4096, nullptr, info_log);
			//TODO: Log error
		}

		GLuint geometry_id = 0;
		if (geometry_code != nullptr) {
			geometry_id = glCreateProgram(GL_GEOMETRY_SHADER);
			glShaderSource(geometry_id, 1, &geometry_code, nullptr);
			glCompileShader(geometry_id);
			glGetShaderiv(geometry_id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(geometry_id, 4096, nullptr, info_log);
				//TODO: Log error
			}
		}

		glAttachShader(new_shader->program_id, vertex_id);
		glAttachShader(new_shader->program_id, fragment_id);
		if (geometry_code != nullptr) glAttachShader(new_shader->program_id, geometry_id);
		glLinkProgram(new_shader->program_id);
		glGetProgramiv(new_shader->program_id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(new_shader->program_id, 4096, nullptr, info_log);
			//TODO: Log error
		}
		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);
		if (geometry_code != nullptr) glDeleteShader(geometry_id);

		return new_shader;
	}
}