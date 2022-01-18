#include "VertexBufferObject.h"

namespace BBB
{
	namespace GLVertex
	{
		void VertexBufferObject::GenBuffers()
		{
			glGenBuffers(1, &VBO);
		}

		void VertexBufferObject::Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
		}

		void VertexBufferObject::SetData(int size, void* data, int usage)
		{
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		}

		void VertexBufferObject::DeleteBuffers()
		{
			glDeleteBuffers(1, &VBO);
		}
	}
}
