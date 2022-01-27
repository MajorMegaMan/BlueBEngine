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
		if (m_layoutArray != nullptr)
		{
			delete[] m_layoutArray;
		}

		m_layoutArray = new VertexAttibute[size];
		m_size = size;
	}

	void VertexLayout::Init(VertexAttibute* attributes, int size)
	{
		Init(size);

		for (int i = 0; i < size; i++)
		{
			m_layoutArray[i] = attributes[i];
		}
	}

	VertexAttibute* VertexLayout::GetBegin()
	{
		return m_layoutArray;
	}

	VertexAttibute& VertexLayout::GetAttribute(int index)
	{
		return m_layoutArray[index];
	}

	void VertexLayout::CalculateStride()
	{
		m_stride = FindStrideToLayout(m_size);
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

	int VertexLayout::GetStride() const
	{
		return m_stride;
	}

	int VertexLayout::FindStrideToLayout(int layoutIndex) const
	{
		int currentStride = 0;
		for (int i = 0; i < layoutIndex; i++)
		{
			currentStride += FindLayoutStride(i);
		}
		return currentStride;
	}

	int VertexLayout::FindLayoutStride(int layoutIndex) const
	{
		return m_layoutArray[layoutIndex].typeSize * m_layoutArray[layoutIndex].size;
	}

	void VertexLayout::SetAttribPointers()
	{
		int runningOffset = 0;
		for (int i = 0; i < m_size; i++)
		{
			m_layoutArray[i].SetPointer(i, m_stride, runningOffset);
			runningOffset += FindLayoutStride(i);
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
