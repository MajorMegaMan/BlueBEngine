#pragma once
#include "Graphics.h"

namespace BBB
{
	namespace GLVertex
	{
		class VertexArrayObject
		{
			// this is the handle for the vertex buffer object
			GLuint VAO = -1;

		public:
			void GenArrays();
			void Bind();
			void DeleteArrays();
		};
	}
}