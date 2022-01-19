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


	public:
		virtual void Generate();
		virtual void Delete();

		Mesh();
		Mesh(const Mesh& other) = delete;
		Mesh& operator=(const Mesh& other) = delete;
		~Mesh();

		void SetVertices(float* verticesArray, int size);

		void VertexAttributePointer(GLuint layoutIndex, GLint size, GLenum type, GLboolean normalized, GLsizei stride, int pointer);

		void Bind();

		void Draw(int verticesCount);
	};
}