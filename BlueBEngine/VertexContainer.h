#pragma once
#include "VertexLayout.h"

// This is a container that contains the vertice array that is to be sent to the GPU.
// It has helpful functions to manage the data that is to be sent.

// This is a multitype array as the user changes vertex data with a specified vetex Index and the layout to be changed aswell.

// Uses VertexLayout for the layout order

//			Layout 0		 Layout 1			Layout 2
// Vertex : Vec3 pos,		 Vec3 colour,		Vec2 uv
// 0      : {-0.5,-0.5, 0.0},{ 1.0, 1.0, 1.0},	{0.0,0.0}
// 1      : { 0.5,-0.5, 0.0},{ 0.0, 1.0, 1.0},	{0.0,0.0}
// 2      : { 0.0, 0.5, 0.0},{ 1.0, 1.0, 0.0},	{0.0,0.0}

// We can change the colour of vertex 2 with 
//		void SetVertex(2, 1, (void*)Vec3{ 0.0, 0.0, 0.5 });

namespace BBB
{
	class VertexContainer
	{
		void* m_vertexArray = nullptr;
		const VertexLayout* p_layout = nullptr;
		int m_totalLayoutStride = 0;
		int m_verticeCount = 0;

	public:

		VertexContainer();
		VertexContainer(const VertexContainer& other) = delete;
		VertexContainer& operator=(const VertexContainer& other) = delete;
		~VertexContainer();

		void Init(const VertexLayout& layout, unsigned int verticeCount);

		const VertexLayout* GetLayout() const;

		void* GetVertexArray() const;
		int GetVerticeCount() const;

		// Choose 
		void SetVertex(unsigned int vertexIndex, unsigned int layoutIndex, void* data);
	};
}