#include "RenderBatch.hpp"
#include <Yeno/Log.hpp>
#include <cstdlib>

namespace Yeno
{
	RenderBatch::RenderBatch()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		if (Config::use_persistent_mapping) {
			glBufferStorage(GL_ARRAY_BUFFER, Config::batch_size * sizeof(Vertex), nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_WRITE_BIT);
			vertices = (Vertex *)glMapBufferRange(GL_ARRAY_BUFFER, 0, Config::batch_size * sizeof(Vertex), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
		}
		else
		{
			vertices = (Vertex *)malloc(Config::batch_size * sizeof(Vertex));
			if (vertices == nullptr) {
				Log::Error("Error: Failed to allocate %d bytes for RenderBatch", Config::batch_size * sizeof(Vertex));
			}
			glBufferData(GL_ARRAY_BUFFER, Config::batch_size * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		}
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0); //Vertex position/Texture coordinate
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(4 * sizeof(GLfloat))); //Vertex colour
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, sizeof(Vertex), (void *)(8 * sizeof(GLfloat))); //Texture sampler
	}

	RenderBatch::~RenderBatch()
	{
		glBindVertexArray(vao);
		if (!Config::use_persistent_mapping) {
			free(vertices);
		}
		else {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			vertices = nullptr;
		}
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	void RenderBatch::Render()
	{
		glBindVertexArray(vao);
		if (!Config::use_persistent_mapping) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * sizeof(Vertex), vertices);
		}
		glDrawArrays(GL_TRIANGLES, 0, vertex_count);
	}

	void RenderBatch::Clear()
	{
		vertex_count = 0;
	}

	void RenderBatch::AddVertex(float x, float y, float r, float g, float b, float a)
	{
		if (vertices != nullptr && vertex_count < Config::batch_size) {
			vertices[vertex_count++] = {x, y, 0.0, 0.0f, r, g, b, a, 0};
		}
	}
}