#pragma once
#include "VoronoiBiSector.h"

struct VoronoiPoint
{
	Vector2 point;
	const DelPoint* delPoints[3];
	VoronoiBiSector neighbours[3];

	int index = 0;

	VoronoiPoint()
	{
		delPoints[0] = nullptr;
		delPoints[1] = nullptr;
		delPoints[2] = nullptr;
	}

	VoronoiPoint(const DelTri& triangle);

	void SetValues(const DelTri& triangle);
	void FindNeighbours(const VoronoiPoint* vPointArray, const DelTri& triangle);
};