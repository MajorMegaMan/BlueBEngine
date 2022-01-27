#pragma once
#include "Mesh.h"
#include "ElementBufferObject.h"

namespace BBB
{
	class IndexedMesh : public Mesh
	{
		GLVertex::ElementBufferObject EBO;

		DynamicArray<unsigned int> indices;

	public:

		void Generate() override;
		void Delete() override;
		void SetIndices(unsigned int* indicesArray, int size);

		// to be used after indices has been filled
		void ApplyIndices();

		void Draw(GLHandles::ShaderProgram& shader) override;
	};
}