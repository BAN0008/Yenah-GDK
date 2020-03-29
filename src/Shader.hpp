#pragma once
#include <glad/glad.h>

namespace Yenah
{
	class Shader
	{
	public:
		static GLuint uniform_buffer;

		static Shader *default_shader;

		static void Initialize();
		static void Cleanup();
		static Shader *CreateFromStrings(const char *vertex_code, const char *fragment_code, const char *geometry_code = nullptr);
		~Shader();

		void Bind();
	private:
		Shader();
		GLuint program_id;
	};
}