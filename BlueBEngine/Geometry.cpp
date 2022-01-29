#include "Geometry.h"

namespace BBB
{
	void InitialiseQuad(Mesh& mesh, const VertexLayout& layout, int positionLayoutIndex)
	{
		mesh.vertices.Init(layout, 6);

		// positions
		glm::vec3 vertices[] = {
		{ 0.5f,  0.5f, 0.0f},  // top right
		{ 0.5f, -0.5f, 0.0f},  // bottom right
		{-0.5f,  0.5f, 0.0f},   // top left 

		{ 0.5f, -0.5f, 0.0f},  // bottom right
		{-0.5f, -0.5f, 0.0f},  // bottom left
		{-0.5f,  0.5f, 0.0f}   // top left 
		};

		for (int i = 0; i < 6; i++)
		{
			mesh.vertices.SetVertex(i, positionLayoutIndex, vertices + i);
		}
	}

	void InitialiseIndexedQuad(IndexedMesh& indexedMesh, const VertexLayout& layout, int positionLayoutIndex)
	{
		indexedMesh.vertices.Init(layout, 4);

		// positions
		glm::vec3 vertices[] = {
		{ 0.5f,  0.5f, 0.0f},  // top right
		{ 0.5f, -0.5f, 0.0f},  // bottom right
		{-0.5f, -0.5f, 0.0f},  // bottom left
		{-0.5f,  0.5f, 0.0f}   // top left 
		};

		for (int i = 0; i < 4; i++)
		{
			indexedMesh.vertices.SetVertex(i, positionLayoutIndex, vertices + i);
		}

		unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
		};

		// apply indices to mesh
		indexedMesh.SetIndices(indices, 6);
	}

	void InitialiseIndexedTriWithCentre(glm::vec3* positions, IndexedMesh& indexedMesh, const VertexLayout& layout, int positionLayoutIndex)
	{
		indexedMesh.vertices.Init(layout, 4);

		glm::vec3 centre = (positions[0] + positions[1] + positions[2]);
		centre = centre / 3.0f;

		// positions
		glm::vec3 vertices[] = {
		positions[0],
		positions[1],
		positions[2],
		centre
		};

		for (int i = 0; i < 4; i++)
		{
			indexedMesh.vertices.SetVertex(i, positionLayoutIndex, vertices + i);
		}

		unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,
		1, 2, 3,
		2, 0, 3
		};

		// apply indices to mesh
		indexedMesh.SetIndices(indices, 9);
	}
}