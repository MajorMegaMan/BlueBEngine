#include "VoronoiShape.h"

VoronoiShape::VoronoiShape()
{
	
}

VoronoiShape::~VoronoiShape()
{
	
}

void VoronoiShape::AddPoint(Vector2 vPoint)
{
	m_vertices.PushBack(vPoint);
}

Vector2* VoronoiShape::GetVertices(int& out_size)
{
	out_size = m_vertices.GetSize();
	return m_vertices.GetArray();
}

void VoronoiShape::Resize()
{
	
}

void VoronoiShape::GiftWrap()
{
	// Check shape has enough points
	int vertCount = m_vertices.GetSize();
	if (vertCount < 3)
	{
		// This shape has less than three vertices. More points should be added before trying to giftwrap it.
		// Depending on the situation, this could be intended but it will still need at least 3 points if this is intended to be used as a shape.
		return;
	}

	Vector2* vertArray = m_vertices.GetArray();
	// Initialise hull
	DLinkedList<Vector2> hull;

	// Find Left most point
	int leftMost = 0; // index of points, not vPoints
	for (int i = 1; i < vertCount; i++)
	{
		if (vertArray[i].x < vertArray[leftMost].x)
		{
			leftMost = i;
		}
	}

	// start from leftmost, keep moving counter clockwise until reach start position again
	int p = leftMost;
	int q = 0;
	do
	{
		// Add current to hull result
		hull.PushBack(vertArray[p]);

		// Search for a point 'q' such that orientation(p, x,
		// q) is counterclockwise for all points 'x'. The idea
		// is to keep track of last visited most counterclock-
		// wise point in q. If any point 'i' is more counterclock-
		// wise than q, then update q.
		q = (p + 1) % vertCount;
		for (int i = 0; i < vertCount; i++)
		{
			// If i is more counterclockwise than current q, then
			// update q
			if(Vector2::PointIsRightOfLine(vertArray[p], vertArray[i], vertArray[q]))
			{
				q = i;
			}
		}

		// Now q is the most counterclockwise with respect to p
		// Set p as q for next iteration, so that q is added to
		// result 'hull'
		p = q;
	} while (p != leftMost);

	// Finish result
	auto node = hull.head;
	int currentIndex = 0;
	while (node != nullptr)
	{
		vertArray[currentIndex] = node->value;
		currentIndex++;
		node = node->next;
	}
}

void VoronoiShape::AddNeighbour(const VoronoiShape& neighbour)
{
	m_neighbours.PushBack(&neighbour);
}

const VoronoiShape* VoronoiShape::GetNeighbour(int index)
{
	return m_neighbours.GetValue(index);
}

int VoronoiShape::GetNeighbourCount()
{
	return m_neighbours.GetSize();
}
