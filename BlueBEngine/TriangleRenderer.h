#pragma once
#include "Model.h"
#include "Geometry.h"

using namespace BBB;

struct Triangle
{
	glm::vec3 positions[3];
	glm::vec4 colour = { 1.0f, 1.0f, 1.0f, 1.0f };

	glm::vec3 GetCentre()
	{
		glm::vec3 result = positions[0] + positions[1] + positions[2];
		result /= 3.0f;
		return result;
	}

	static float sign(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	static bool PointInTriangle(glm::vec3 point, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
	{
		float d1, d2, d3;
		bool has_neg, has_pos;

		d1 = sign(point, v1, v2);
		d2 = sign(point, v2, v3);
		d3 = sign(point, v3, v1);

		has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
		has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

		return !(has_neg && has_pos);
	}

	bool PointInTriangle(glm::vec3 point)
	{
		return PointInTriangle(point, positions[0], positions[1], positions[2]);
	}
};

class TriangleRender
{
	Model m_model;
	Shader m_shader;
	Mesh m_mesh;

	DynamicArray<Triangle> m_tris;

	DynamicArray<glm::vec3> m_constructingTri;

public:
	TriangleRender();
	~TriangleRender();

	TriangleRender(const TriangleRender& other) = delete;
	TriangleRender& operator=(const TriangleRender& other) = delete;

	void AddToTriConstruct(glm::vec3 position);
	void ClearTriConstruct();

	void ClearTriangles();

	void Draw(glm::mat4x4 transform);

	void SetTriangleColour(int triIndex, glm::vec4 colour);

	Triangle* GetTriArray(int& out_size);

	void ApplyVertices();

private:
	void UpdateTriangles();

	void UpdateTriangle(VertexContainer& vertices, int index);

	void UpdateTriPositions(VertexContainer& vertices, int index);

	void UpdateTriColour(VertexContainer& vertices, int index, glm::vec4 colour);
};