#pragma once
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Texture2D.h"
#include <Utilities/DynamicArray.h>
#include "VertexContainer.h"

namespace BBB
{
	class Mesh
	{
	protected:
		GLVertex::VertexArrayObject VAO;
		GLVertex::VertexBufferObject VBO;

		GLenum usage = GL_STATIC_DRAW;

		bool isLoaded = false;

	public:
		VertexContainer vertices;

		virtual void Generate();
		virtual void Delete();

		Mesh();
		Mesh(const Mesh& other) = delete;
		Mesh& operator=(const Mesh& other) = delete;
		~Mesh();

		void SetVertices(float* verticesArray, int size);

		// This should be called after the vertex container has been filled to apply the vertices to the vbo
		void ApplyVertices();

		void SetUsage(GLenum usage);

		void Bind();

		virtual void Draw(GLHandles::ShaderProgram& shader);
	};
}