#include "RenderBatch.hpp"
#include <cstdlib>
#define BATCH_SIZE 100000 // TODO: Dynamic batch size

namespace Yenah
{
	RenderBatch::RenderBatch()
	{
		vertices = (Vertex *)malloc(sizeof(Vertex) * BATCH_SIZE);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, BATCH_SIZE * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0); // Vertex position / Texture coordinate
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

		glEnableVertexAttribArray(1); // Vertex colour
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(4 * sizeof(float)));

		glBindVertexArray(0);
	}

	RenderBatch::~RenderBatch()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		vertex_count = 0;
		free(vertices);
	}

	void RenderBatch::AddVertex(float x, float y, float r, float g, float b, float a)
	{
		if (vertex_count < BATCH_SIZE) {
			vertices[vertex_count++] = {x, y, 0.0f, 0.0f, r, g, b, a};
		}
	}

	void RenderBatch::Clear()
	{
		vertex_count = 0;
	}

	void RenderBatch::Render()
	{
		glBindVertexArray(vao);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * sizeof(Vertex), vertices);
		glDrawArrays(GL_TRIANGLES, 0, vertex_count);
		glBindVertexArray(0);
	}
}