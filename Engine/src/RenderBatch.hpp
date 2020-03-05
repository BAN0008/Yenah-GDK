#pragma once
#include "Config.hpp"
#include <glad/glad.h>

namespace Yeno
{
	struct Vertex
	{
		GLfloat x, y;
		GLfloat tx, ty;
		GLfloat r, g, b, a;
		GLint sampler;
	};

	class RenderBatch
	{
	public:
		RenderBatch();
		~RenderBatch();

		void Render();
		void Clear();

		void AddVertex(float x, float y, float r, float g, float b, float a);
	private:
		Vertex *vertices = nullptr;
		int vertex_count = 0;
		GLuint vao = 0;
		GLuint vbo = 0;
	};
}