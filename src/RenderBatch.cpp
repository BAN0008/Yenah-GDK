#include "RenderBatch.hpp"
#include "Log.hpp" // TODO: Delete me
#include <cstdlib>
#define BATCH_SIZE 100000 // TODO: Dynamic batch size

namespace Yenah
{
	namespace RenderBatch
	{
		Vertex *vertices = nullptr;
		unsigned long vertex_count = 0;
		GLuint vao = 0, vbo = 0;

		void Initialize()
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

		void Cleanup()
		{
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
			vertex_count = 0;
			free(vertices);
		}

		void AddVertex(Vertex *vertex)
		{
			if (vertex_count < BATCH_SIZE) {
				vertices[vertex_count++] = *vertex;
			}
		}

		unsigned int GetVertexCount()
		{
			return vertex_count;
		}

		void Flush()
		{
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * sizeof(Vertex), vertices);
			glDrawArrays(GL_TRIANGLES, 0, vertex_count);
			glBindVertexArray(0);

			vertex_count = 0;
		}
	}
}