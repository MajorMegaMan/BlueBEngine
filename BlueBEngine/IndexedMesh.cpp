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
		EBO.Bind();
		EBO.SetData(size * sizeof(unsigned int), indicesArray, GL_STATIC_DRAW);
	}

	void IndexedMesh::IDraw(GLsizei indiceCount, GLenum type)
	{
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, indiceCount, type, 0);
	}
}
