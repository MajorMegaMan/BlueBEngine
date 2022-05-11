#pragma once
#include "VoronoiShape.h"

class VoronoiDiagram
{
public:
	DelaunayMap m_delMap;

	VoronoiPoint* m_vPointArray = nullptr;
	VoronoiShape* m_vShapeArray = nullptr;

	VoronoiDiagram() {}
	VoronoiDiagram(const Vector2* pointArray, int pointCount);
	VoronoiDiagram(const DelPoint* pointArray, int pointCount);
	VoronoiDiagram(const VoronoiDiagram& other) = delete;
	VoronoiDiagram& operator=(const VoronoiDiagram& other) = delete;
	~VoronoiDiagram();

	void Init(const Vector2* pointArray, int pointCount);
	//void Init(const DelPoint* pointArray, int pointCount);
	void Clear();

private:
	void CreatePointArray();
	void ClearPointArray();

	void CreateShapeArray();
	void ClearShapeArray();

public:
	int GetVPointCount()
	{
		return m_delMap.GetTriCount();
	}

	int GetVShapeCount()
	{
		return m_delMap.GetPointCount();
	}
};