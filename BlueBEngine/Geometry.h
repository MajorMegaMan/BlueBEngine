#pragma once
#include "IndexedMesh.h"
#include "Maths.h"

namespace BBB
{
	void InitialiseQuad(Mesh& mesh, const VertexLayout& layout, int positionLayoutIndex = 0);

	void InitialiseIndexedQuad(IndexedMesh& mesh, const VertexLayout& layout, int positionLayoutIndex = 0);

	void InitialiseIndexedTriWithCentre(glm::vec3* positions, IndexedMesh& mesh, const VertexLayout& layout, int positionLayoutIndex = 0);
}