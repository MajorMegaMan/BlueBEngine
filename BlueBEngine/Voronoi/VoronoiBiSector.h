#pragma once
#include "DelaunayMap.h"

struct VoronoiPoint;

struct VoronoiBiSector
{
	Vector2 direction;
	const VoronoiPoint* end = nullptr;

	void SetEnd(const VoronoiPoint* start, const VoronoiPoint* target);

	void CalcBiSector(Vector2 start, Vector2 end);
};