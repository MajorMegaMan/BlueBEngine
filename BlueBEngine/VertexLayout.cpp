#include "VertexLayout.h"

namespace BBB
{
	VertexLayout::~VertexLayout()
	{
		if (m_layoutArray != nullptr)
		{
			delete[] m_layoutArray;
			m_layoutArray = nullptr;
			m_size = 0;
		}
	}

	void VertexLayout::Init(int size)
	{
		m_layoutArray = new VertexAttibute[size];
		m_size = size;
	}

	VertexAttibute* VertexLayout::GetBegin()
	{
		return m_layoutArray;
	}

	VertexAttibute& VertexLayout::GetAttribute(int index)
	{
		return m_layoutArray[index];
	}

	int VertexLayout::GetLayoutSize(int index) const
	{
		return m_layoutArray[index].size;
	}

	int VertexLayout::FindTotalSize() const
	{
		int totalSize = 0;
		for (int i = 0; i < m_size; i++)
		{
			totalSize += m_layoutArray[i].size;
		}
		return totalSize;
	}

	int VertexLayout::GetLayoutStride(int index) const
	{
		return m_layoutArray[index].stride;
	}

	int VertexLayout::FindStrideToLayout(int index) const
	{
		int stride = 0;
		for (int i = 0; i < index; i++)
		{
			stride += m_layoutArray[i].stride;
		}
		return stride;
	}

	int VertexLayout::FindTotalStride() const
	{
		int totalStride = 0;
		for (int i = 0; i < m_size; i++)
		{
			totalStride += m_layoutArray[i].stride;
		}
		return totalStride;
	}
	void VertexLayout::SetAttribPointers()
	{
		int runningOffset = 0;
		for (int i = 0; i < m_size; i++)
		{
			m_layoutArray[i].SetPointer(i, runningOffset);
			runningOffset += m_layoutArray[i].stride;
		}
	}
	void VertexLayout::Enable()
	{
		for (int i = 0; i < m_size; i++)
		{
			VertexAttibute::EnableAttribArray(i);
		}
	}
}
