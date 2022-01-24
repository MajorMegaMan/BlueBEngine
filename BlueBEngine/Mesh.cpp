#include "Mesh.h"

namespace BBB
{
	void Mesh::Generate()
	{
		VAO.GenArrays();
		VBO.GenBuffers();
	}

	void Mesh::Delete()
	{
		VBO.DeleteBuffers();
		VAO.DeleteArrays();
	}

	Mesh::Mesh()
	{
		
	}

	Mesh::~Mesh()
	{
		
	}

	void Mesh::SetVertices(float* verticesArray, int size)
	{
		VAO.Bind();
		VBO.Bind();
		VBO.SetData(size * sizeof(float), verticesArray, usage);
	}

	void Mesh::SetUsage(GLenum usage)
	{
		this->usage = usage;
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
