#include "Mesh.h"

namespace BBB
{
	Mesh::Mesh()
	{
		VAO.GenArrays();
		VBO.GenBuffers();
	}
	Mesh::~Mesh()
	{
		VBO.DeleteBuffers();
		VAO.DeleteArrays();
	}

	void Mesh::SetVertices(float* verticesArray, int size)
	{
		VAO.Bind();
		VBO.Bind();
		VBO.SetData(size * sizeof(float), verticesArray, GL_STATIC_DRAW);
	}

	void Mesh::VertexAttributePointer(int layoutIndex, int size, int type, int normalized, int stride, int pointer)
	{
		glVertexAttribPointer(layoutIndex, size, type, normalized, stride, (void*)pointer);
		glEnableVertexAttribArray(layoutIndex);
	}

	void Mesh::Bind()
	{
		VAO.Bind();
	}

	void Mesh::Draw(int verticesCount)
	{
		Bind();
		glDrawArrays(GL_TRIANGLES, 0, verticesCount);
	}
}
