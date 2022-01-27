#include "IndexedMesh.h"

namespace BBB
{
	void IndexedMesh::Generate()
	{
		VAO.GenArrays();
		VBO.GenBuffers();
		EBO.GenBuffers();
	}

	void IndexedMesh::Delete()
	{
		VBO.DeleteBuffers();
		EBO.DeleteBuffers();
		VAO.DeleteArrays();
	}

	void IndexedMesh::SetIndices(unsigned int* indicesArray, int size)
	{
		indices.Clear();
		indices.Reserve(size);
		for (int i = 0; i < 6; i++)
		{
			indices.PushBack(indicesArray[i]);
		}
	}

	void IndexedMesh::ApplyIndices()
	{
		EBO.Bind();
		EBO.SetData(indices.GetSize() * sizeof(unsigned int), indices.GetArray(), usage);
	}

	void IndexedMesh::Draw(GLHandles::ShaderProgram& shader)
	{
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, indices.GetSize(), GL_UNSIGNED_INT, 0);
	}
}
