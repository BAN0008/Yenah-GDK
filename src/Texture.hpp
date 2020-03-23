#pragma once
#include <glad/glad.h>
#include <vector>

namespace Yenah
{
	class Texture
	{
	public:
		Texture(const char *fname);
		~Texture();

		static std::vector<Texture *> textures;

		void Bind();
		GLuint GetID();
	private:
		GLuint texture_id = 0;
		int width, height;
	};
}