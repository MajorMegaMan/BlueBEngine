#include "Mesh.h"

namespace BBB
{
	void Mesh::Generate()
	{
		// Try to delete first before Generating
		Delete();

		VAO.GenArrays();
		VBO.GenBuffers();
	}

	void Mesh::Delete()
	{
		if (isLoaded)
		{
			VBO.DeleteBuffers();
			VAO.DeleteArrays();
			isLoaded = false;
		}
	}

	Mesh::Mesh()
	{
		
	}

	Mesh::~Mesh()
	{
		Delete();
	}

	void Mesh::SetVertices(float* verticesArray, int size)
	{
		VAO.Bind();
		VBO.Bind();
		VBO.SetData(size * sizeof(float), verticesArray, usage);
	}

	void Mesh::ApplyVertices()
	{
		SetVertices((float*)vertices.GetVertexArray(), vertices.GetVerticeCount() * vertices.GetLayout()->FindTotalSize());
	}

	void Mesh::SetUsage(GLenum usage)
	{
		this->usage = usage;
	}

	void Mesh::Bind()
	{
		VAO.Bind();
	}

	void Mesh::Draw(GLHandles::ShaderProgram& shader)
	{
		Bind();
		glDrawArrays(GL_TRIANGLES, 0, vertices.GetVerticeCount());
	}
}
