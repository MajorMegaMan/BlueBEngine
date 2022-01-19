#include "ElementBufferObject.h"

namespace BBB
{
	namespace GLVertex
	{
		void ElementBufferObject::GenBuffers()
		{
			glGenBuffers(1, &EBO);
		}

		void ElementBufferObject::Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		}

		void ElementBufferObject::SetData(GLsizeiptr size, void* data, GLenum usage)
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
		}

		void ElementBufferObject::DeleteBuffers()
		{
			glDeleteBuffers(1, &EBO);
		}
	}
}