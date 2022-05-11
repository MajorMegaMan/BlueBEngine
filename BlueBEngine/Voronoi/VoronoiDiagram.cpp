#include "VoronoiDiagram.h"

VoronoiDiagram::VoronoiDiagram(const Vector2* pointArray, int pointCount)
{
	Init(pointArray, pointCount);
}

VoronoiDiagram::VoronoiDiagram(const DelPoint* pointArray, int pointCount)
{
	Init(pointArray, pointCount);
}

VoronoiDiagram::~VoronoiDiagram()
{
	Clear();
}

void VoronoiDiagram::Init(const Vector2* pointArray, int pointCount)
{
	Clear();
	m_delMap.Init(pointArray, pointCount);

	CreatePointArray();

	CreateShapeArray();
}

void VoronoiDiagram::Clear()
{
	m_delMap.Clear();
	ClearPointArray();
	ClearShapeArray();
}

void VoronoiDiagram::CreatePointArray()
{
	int vPointCount = m_delMap.GetTriCount();

	m_vPointArray = new VoronoiPoint[vPointCount];
	const DelTri* triangleArray = m_delMap.GetTriBegin();

	// Find point values from circumcircles of triangles
	for (int i = 0; i < vPointCount; i++)
	{
		m_vPointArray[i].SetValues(triangleArray[i]);
	}

	// find neighbours after the inital v points have been set
	for (int i = 0; i < vPointCount; i++)
	{
		m_vPointArray[i].FindNeighbours(m_vPointArray, triangleArray[i]);
	}
}

void VoronoiDiagram::ClearPointArray()
{
	if (m_vPointArray != nullptr)
	{
		delete[] m_vPointArray;
		m_vPointArray = nullptr;
	}
}

void VoronoiDiagram::CreateShapeArray()
{
	// initialise array to delpoint count
	int shapeCount = m_delMap.GetPointCount();
	m_vShapeArray = new VoronoiShape[shapeCount];

	for (int i = 0; i < shapeCount; i++)
	{
		m_vShapeArray[i].index = i;
	}

	// Find vertices from vPoints and their respective triangle
	int vPointCount = GetVPointCount();
	for (int i = 0; i < vPointCount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			auto delPoint = m_vPointArray[i].delPoints[j];
			m_vShapeArray[delPoint->index].AddPoint(m_vPointArray[i].point);
			auto biSector = m_vPointArray[i].neighbours[j];
			if (biSector.end == nullptr)
			{
				int nextIndex = (j + 1) % 3;
				auto nextDel = m_vPointArray[i].delPoints[nextIndex];
				m_vShapeArray[delPoint->index].AddPoint(m_vPointArray[i].point + biSector.direction * 100.0f);
				m_vShapeArray[nextDel->index].AddPoint(m_vPointArray[i].point + biSector.direction * 100.0f);
			}
		}
	}

	// ensure that vertices are ordered in a counter clockwise pattern
	for (int i = 0; i < shapeCount; i++)
	{
		m_vShapeArray[i].GiftWrap();
	}

	// for each triangle add each edge as a vshape neighbour
	for (int i = 0; i < vPointCount; i++)
	{
		const DelTri* delTri = &m_delMap.GetTriBegin()[i];
		for (int j = 0; j < 3; j++)
		{
			const DelPoint* start = delTri->GetPoint(j);
			const DelPoint* end = delTri->GetPoint((j + 1) % 3);
			m_vShapeArray[start->index].AddNeighbour(m_vShapeArray[end->index]);
		}
	}
}

void VoronoiDiagram::ClearShapeArray()
{
	if (m_vShapeArray != nullptr)
	{
		delete[] m_vShapeArray;
		m_vShapeArray = nullptr;
	}
}
