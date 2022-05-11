//#include "VoronoiBiSector.h"
#include "VoronoiPoint.h"

void VoronoiBiSector::SetEnd(const VoronoiPoint* start, const VoronoiPoint* target)
{
	end = target;
	direction = target->point - start->point;
}

void VoronoiBiSector::CalcBiSector(Vector2 start, Vector2 end)
{
	Vector2 toMidPoint = (end - start) / 2.0f;

	Vector2 result;
	result.x = toMidPoint.y;
	result.y = -toMidPoint.x;

	direction = result;
}
