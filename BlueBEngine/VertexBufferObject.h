#pragma once
#include "Graphics.h"

namespace BBB
{
	namespace GLVertex
	{
		class VertexBufferObject
		{
			// this is the handle for the vertex buffer object
			GLuint VBO = -1;

		public:
			void GenBuffers();
			void Bind();
			void SetData(GLsizeiptr size, void* data, GLenum usage);
			void DeleteBuffers();
		};
	}
}