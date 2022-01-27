#include "VertexContainer.h"

namespace BBB
{
	VertexContainer::VertexContainer()
	{

	}

	VertexContainer::~VertexContainer()
	{
		if (m_vertexArray != nullptr)
		{
			delete[] m_vertexArray;
			m_vertexArray = nullptr;
		}
	}

	void VertexContainer::Init(const VertexLayout& layout, unsigned int verticeCount)
	{
		if (m_vertexArray != nullptr)
		{
			delete[] m_vertexArray;
		}

		p_layout = &layout;
		m_totalLayoutStride = p_layout->GetStride();
		m_verticeCount = verticeCount;
		m_vertexArray = new char[m_totalLayoutStride * m_verticeCount];
	}

	const VertexLayout* VertexContainer::GetLayout() const
	{
		return p_layout;
	}

	void* VertexContainer::GetVertexArray() const
	{
		return m_vertexArray;
	}

	int VertexContainer::GetVerticeCount() const
	{
		return m_verticeCount;
	}

	void VertexContainer::SetVertex(unsigned int vertexIndex, unsigned int layoutIndex, void* data)
	{
		char* targetVertex = (char*)m_vertexArray + (m_totalLayoutStride * vertexIndex);
		int strideToLayout = p_layout->FindStrideToLayout(layoutIndex);
		char* targetLayout = targetVertex + strideToLayout;
		int layoutStride = p_layout->FindLayoutStride(layoutIndex);
		for (int i = 0; i < layoutStride; i++)
		{
			targetLayout[i] = ((char*)data)[i];
		}
	}
}
