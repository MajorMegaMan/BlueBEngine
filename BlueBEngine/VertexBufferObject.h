#pragma once
#include "Graphics.h"

namespace BBB
{
	namespace GLVertex
	{
		class VertexBufferObject
		{
			// this is the handle for the vertex buffer object
			GLuint VBO;

		public:
			void GenBuffers();
			void Bind();
			void SetData(int size, void* data, int usage);
			void DeleteBuffers();
		};
	}
}