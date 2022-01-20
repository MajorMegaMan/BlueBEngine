#pragma once
#include "VertexAttribute.h"

// This is a class that contains all the desired attributes that will be used in a shader.
// It has useful functions to help get pointer positions in the vertice array that will be sent to the GPU.
// In other words, finding where the colour layout attribute is in a vertex array.

namespace BBB
{
	class VertexLayout
	{
		VertexAttibute* m_layoutArray = nullptr;
		int m_size = 0;
		GLsizei m_stride = 0;

	public:
		VertexLayout() {};
		VertexLayout(const VertexLayout& other) = delete;
		VertexLayout& operator=(const VertexLayout& other) = delete;
		~VertexLayout();

		void Init(int size, GLsizei stride);
		VertexAttibute* GetBegin();
		VertexAttibute& GetAttribute(int index);

		int GetLayoutSize(int index) const;
		int FindTotalSize() const;

		int GetStride() const;
		int FindStrideToLayout(int layoutIndex) const;
		int FindLayoutStride(int layoutIndex) const;

		void SetAttribPointers();
		void Enable();
	};
}