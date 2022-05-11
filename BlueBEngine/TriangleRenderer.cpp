#include "TriangleRenderer.h"
#include "Debug.h"

TriangleRender::TriangleRender()
{
	m_shader.LoadShader("unlitShape.vert", "unlitShape.frag");

	VertexAttribute layouts[2];
	// position
	layouts[0].SetValues(3, GL_FLOAT, GL_FALSE, sizeof(float));
	// colour
	layouts[1].SetValues(4, GL_FLOAT, GL_FALSE, sizeof(float));

	m_shader.SetLayout(layouts, 2);
	m_model.p_mesh = &m_mesh;
	m_model.m_material.SetShader(m_shader);
	m_model.SetModelMatrixName("transform");
	m_model.p_mesh->Generate();
	m_mesh.SetUsage(GL_DYNAMIC_DRAW);

	m_constructingTri.Reserve(3);
}

TriangleRender::~TriangleRender()
{
	
}

void TriangleRender::AddToTriConstruct(glm::vec3 position)
{
	m_constructingTri.PushBack(position);
	if (m_constructingTri.GetSize() == 3)
	{
		Triangle toAdd;
		for (int i = 0; i < 3; i++)
		{
			toAdd.positions[i] = m_constructingTri.GetValue(i);
		}
		m_tris.PushBack(toAdd);
		m_constructingTri.Clear();
		UpdateTriangles();
		ApplyVertices();
	}
}

void TriangleRender::ClearTriConstruct()
{
	m_constructingTri.Clear();
}

void TriangleRender::AddTriangle(Triangle triangle)
{
	m_tris.PushBack(triangle);
}

void TriangleRender::ClearTriangles()
{
	m_tris.Clear();
}

void TriangleRender::Draw(glm::mat4x4 transform)
{
	if (m_tris.GetSize() > 0)
	{
		m_model.Draw(transform);
	}
}

void TriangleRender::SetTriangleColour(int triIndex, glm::vec4 colour)
{
	UpdateTriColour(m_model.p_mesh->vertices, triIndex, colour);
}

Triangle* TriangleRender::GetTriArray(int& out_Size)
{
	out_Size = m_tris.GetSize();
	return m_tris.GetArray();
}

void TriangleRender::ApplyVertices()
{
	m_mesh.ApplyVertices();

	m_shader.EnableLayout();
}

void TriangleRender::UpdateTriangles()
{
	int triCount = m_tris.GetSize();
	if (triCount > 0)
	{
		auto vertices = &(m_model.p_mesh->vertices);
		vertices->Init(m_shader.GetLayout(), triCount * 3);

		for (int i = 0; i < triCount; i++)
		{
			UpdateTriangle(*vertices, i);
		}
	}
}

void TriangleRender::UpdateTriangle(VertexContainer& vertices, int index)
{
	Triangle* tri = &m_tris.GetValue(index);
	glm::vec3 vertsToAdd[3] = {
		tri->positions[0],
		tri->positions[1],
		tri->positions[2],
	};

	int vertexIndex = index * 3;
	for (int i = 0; i < 3; i++)
	{
		vertices.SetVertex(vertexIndex + i, 0, vertsToAdd + i);
		vertices.SetVertex(vertexIndex + i, 1, &tri->colour);
	}
}

void TriangleRender::UpdateTriPositions(VertexContainer& vertices, int index)
{
	Triangle* tri = &m_tris.GetValue(index);
	glm::vec3 vertsToAdd[3] = {
		tri->positions[0],
		tri->positions[1],
		tri->positions[2],
	};

	int vertexIndex = index * 3;
	for (int i = 0; i < 3; i++)
	{
		vertices.SetVertex(vertexIndex + i, 0, vertsToAdd + i);
	}
}

void TriangleRender::UpdateTriColour(VertexContainer& vertices, int index, glm::vec4 colour)
{
	Triangle* tri = &m_tris.GetValue(index);
	tri->colour = colour;

	int vertexIndex = index * 3;
	for (int i = 0; i < 3; i++)
	{
		vertices.SetVertex(vertexIndex + i, 1, &colour);
	}
}
