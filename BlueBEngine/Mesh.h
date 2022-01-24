#pragma once
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

namespace BBB
{
	class Mesh
	{
	protected:
		GLVertex::VertexArrayObject VAO;
		GLVertex::VertexBufferObject VBO;

		GLenum usage = GL_STATIC_DRAW;

	public:
		virtual void Generate();
		virtual void Delete();

		Mesh();
		Mesh(const Mesh& other) = delete;
		Mesh& operator=(const Mesh& other) = delete;
		~Mesh();

		void SetVertices(float* verticesArray, int size);

		void SetUsage(GLenum usage);

		void Bind();

		void Draw(int verticesCount);
	};
}