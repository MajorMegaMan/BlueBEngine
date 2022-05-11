#pragma once
#include "VoronoiPoint.h"
#include "DynamicArray.h"

class VoronoiShape
{
	DynamicArray<Vector2> m_vertices;
	DynamicArray<const VoronoiShape*> m_neighbours;

public:
	int index = 0;

	VoronoiShape();
	VoronoiShape(const VoronoiShape& other) = delete;
	VoronoiShape& operator=(const VoronoiShape& other) = delete;
	~VoronoiShape();

	void AddPoint(Vector2 vPoint);

	Vector2* GetVertices(int& out_size);
	void GiftWrap();

	void AddNeighbour(const VoronoiShape& neighbour);
	const VoronoiShape* GetNeighbour(int index);
	int GetNeighbourCount();

private:
	void Resize();
};