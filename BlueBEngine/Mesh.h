#pragma once
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

namespace BBB
{
	class Mesh
	{
		GLVertex::VertexArrayObject VAO;
		GLVertex::VertexBufferObject VBO;

	public:

		Mesh();
		Mesh(const Mesh& other) = delete;
		Mesh& operator=(const Mesh& other) = delete;
		~Mesh();

		void SetVertices(float* verticesArray, int size);

		void VertexAttributePointer(int layoutIndex, int size, int type, int normalized, int stride, int pointer);

		void Bind();

		void Draw(int verticesCount);
	};
}