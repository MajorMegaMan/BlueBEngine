#include "VoronoiPoint.h"

VoronoiPoint::VoronoiPoint(const DelTri& triangle)
{
	SetValues(triangle);
}

void VoronoiPoint::SetValues(const DelTri& triangle)
{
	point = triangle.CalcCircumcentre();
	index = triangle.index;

	for (int j = 0; j < 3; j++)
	{
		auto vertice = triangle.GetPoint(j);
		delPoints[j] = vertice;
	}
}

void VoronoiPoint::FindNeighbours(const VoronoiPoint* vPointArray, const DelTri& triangle)
{
	for (int j = 0; j < 3; j++)
	{
		auto triNeighbour = triangle.neighbours[j];
		if (triNeighbour != nullptr)
		{
			neighbours[j].SetEnd(this, &vPointArray[triNeighbour->index]);
		}
		else
		{
			int endIndex = (j + 1) % 3;
			neighbours[j].CalcBiSector(*triangle.GetPoint(j), *triangle.GetPoint(endIndex));
		}
	}
}
