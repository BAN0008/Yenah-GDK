#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#define BATCH_SIZE 100000 // TODO: Dynamic batch size

namespace Yenah
{
	struct Vertex
	{
		float x, y, z, w;
		float r, g, b, a;
	};

	namespace RenderBatch
	{
		void Initialize();
		void Cleanup();

		void AddVertex(Vertex *vertex);

		unsigned int GetVertexCount();
		void Flush();
	};
}