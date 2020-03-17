#pragma once
#include <glad/glad.h>

namespace Yenah
{
	struct Vertex
	{
		float x, y, z, w;
		float r, g, b, a;
	};

	class RenderBatch
	{
	public:
		RenderBatch();
		~RenderBatch();

		void AddVertex(float x, float y, float r, float g, float b, float a);

		void Clear();
		void Render();
	private:
		Vertex *vertices;
		unsigned long vertex_count = 0;
		GLuint vao = 0, vbo = 0;
	};
}