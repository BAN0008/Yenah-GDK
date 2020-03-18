#pragma once
#include <glad/glad.h>

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