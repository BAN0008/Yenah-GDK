#include "Renderer.hpp"
#include "Shader.hpp"
#include "Log.hpp"

#include <glad/glad.h>

namespace Yenah
{
	bool Renderer::Initialize()
	{
		if (!gladLoadGL()) {
			Log::Fatal("Failed to initialize OpenGL");
			return false;
		}

		// Check OpenGL version
		int gl_major, gl_minor;
		glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
		glGetIntegerv(GL_MINOR_VERSION, &gl_minor);
		if (gl_major * 10 + gl_minor < 32) {
			Log::Fatal("OpenGL version 3.2 or higher is required");
			Log::Fatal("OpenGL version %d.%d provided", gl_major, gl_minor);
			return false;
		}
		Log::Info("Using OpenGL %s", glGetString(GL_VERSION));

		Shader::Initialize();
		return true;
	}

	void Renderer::Cleanup()
	{
		//TODO: Check if the default shader needs to be destroyed
	}
}