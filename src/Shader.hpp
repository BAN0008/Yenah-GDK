#pragma once
#include <glad/glad.h>

namespace Yenah
{
	class Shader
	{
	public:
		static GLuint uniform_buffer;

		static void Initialize();
		static Shader *CreateFromStrings(const char *vertex_code, const char *fragment_code, const char *geometry_code = nullptr);
		~Shader();

		void Bind();
	private:
		Shader();
		static Shader *default_shader;
		GLuint program_id;
	};
}