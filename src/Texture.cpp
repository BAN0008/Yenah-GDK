#include "Texture.hpp"
#include "Log.hpp"
#include "Lua.hpp"
#include <stb_image.h>

namespace Yenah
{
	std::vector<Texture *> Texture::textures;
	
	Texture::Texture(const char *fname)
	{
		stbi_set_flip_vertically_on_load(true);
		unsigned char *image_data = stbi_load(fname, &width, &height, nullptr, 4);
		if (image_data == nullptr) {
			Log::Error("Failed to load image %s", fname);
			return;
		}

		Log::Info("Loaded %dx%d texture", width, height);

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(image_data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &texture_id);
	}

	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}

	GLuint Texture::GetID()
	{
		return texture_id;
	}

	FFI_EXPORT void *CreateTexture(const char *fname)
	{
		for (unsigned long i = 0; i < Texture::textures.size(); i++) {
			if (Texture::textures[i] == nullptr) {
				Texture::textures[i] = new Texture(fname);
				return (void *)i;
			}
		}
		Texture::textures.push_back(new Texture(fname));
		return (void *)(Texture::textures.size() - 1);
	}

	FFI_EXPORT void DeleteTexture(void *id)
	{
		Log::Info("Texture %lu deleted", (unsigned long)id);
		delete Texture::textures[(unsigned long)id];
		Texture::textures[(unsigned long)id] = nullptr;
	}
}