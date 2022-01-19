#pragma once
#include "Mesh.h"
#include "ElementBufferObject.h"

namespace BBB
{
	class IndexedMesh : public Mesh
	{
		GLVertex::ElementBufferObject EBO;


	public:
		void Generate() override;
		void Delete() override;
		void SetIndices(unsigned int* indicesArray, int size);

		void IDraw(GLsizei indiceCount, GLenum type);
	};
}