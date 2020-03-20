#pragma once
#include <glad/glad.h>

namespace Yenah
{
	class Texture
	{
	public:
		Texture(const char *fname);
		~Texture();

		void Bind();
		GLuint GetID();
	private:
		GLuint texture_id = 0;
		int width, height;
	};
}