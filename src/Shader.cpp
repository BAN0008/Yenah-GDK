#include "Shader.hpp"
#include "Log.hpp"
#include <glm/glm.hpp>

const char *default_vertex_code = R"(
#version 150 core
#extension GL_ARB_explicit_attrib_location : enable
layout (location = 0) in vec4 vertex;
layout (location = 1) in vec4 colour;
layout (location = 2) in int sampler;

out vec4 frag_colour;

layout (std140) uniform matrices
{
	mat4 projection;
	mat4 view;
};

void main()
{
	frag_colour = colour;
	gl_Position = projection * view * vec4(vertex.xy, 0.0, 1.0);
})";

const char *default_fragment_code = R"(
#version 150 core
in vec4 frag_colour;
out vec4 out_frag_colour;

void main()
{
	out_frag_colour = frag_colour;
})";

namespace Yenah
{
	Shader *Shader::default_shader = nullptr;
	GLuint Shader::uniform_buffer = 0;

	Shader::Shader()
	{
		program_id = glCreateProgram();
	}
	Shader::~Shader()
	{
		glDeleteProgram(program_id);
	}

	void Shader::Initialize()
	{
		glGenBuffers(1, &uniform_buffer);
		glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, uniform_buffer, 0, sizeof(glm::mat4) * 2);

		default_shader = CreateFromStrings(default_vertex_code, default_fragment_code);
		default_shader->Bind();
	}

	Shader *Shader::CreateFromStrings(const char *vertex_code, const char *fragment_code, const char *geometry_code)
	{
		Shader *new_shader = new Shader();
		GLint success;
		GLchar info_log[4096];

		GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_id, 1, &vertex_code, nullptr);
		glCompileShader(vertex_id);
		glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex_id, 4096, nullptr, info_log);
			Log::Error("Failed to compile vertex shader: %s", info_log);
		}

		GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_id, 1, &fragment_code, nullptr);
		glCompileShader(fragment_id);
		glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment_id, 4096, nullptr, info_log);
			Log::Error("Failed to compile fragment shader: %s", info_log);
		}

		GLuint geometry_id = 0;
		if (geometry_code != nullptr) {
			geometry_id = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry_id, 1, &geometry_code, nullptr);
			glCompileShader(geometry_id);
			glGetShaderiv(geometry_id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(geometry_id, 4096, nullptr, info_log);
				Log::Error("Failed to compile geometry shader: %s", info_log);
			}
		}

		glAttachShader(new_shader->program_id, vertex_id);
		glAttachShader(new_shader->program_id, fragment_id);
		if (geometry_code != nullptr) glAttachShader(new_shader->program_id, geometry_id);
		glLinkProgram(new_shader->program_id);
		glGetProgramiv(new_shader->program_id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(new_shader->program_id, 4096, nullptr, info_log);
			Log::Error("Failed to link shader program: %s", info_log);
		}
		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);
		if (geometry_code != nullptr) glDeleteShader(geometry_id);

		GLuint index = glGetUniformBlockIndex(new_shader->program_id, "matrices");
		glUniformBlockBinding(new_shader->program_id, index, 0);

		return new_shader;
	}

	void Shader::Bind()
	{
		glUseProgram(program_id);
	}
}