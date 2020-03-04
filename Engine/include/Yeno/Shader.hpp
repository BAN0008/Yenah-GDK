#pragma once
#include <glad/glad.h>

namespace Yeno
{
	class Shader
	{
	public:
		static Shader *CreateFromStrings(const char *vertex_code, const char *fragment_code, const char *geometry_code = nullptr);
		~Shader();

		void Bind();
	private:
		Shader();
		GLuint program_id;
	};
}