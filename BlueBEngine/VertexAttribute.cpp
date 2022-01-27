#include "VertexAttribute.h"

namespace BBB
{
	void VertexAttribute::SetValues(GLint size, GLenum type, GLboolean normalized, GLsizei typeSize)
	{
		this->size = size;
		this->type = type;
		this->normalized = normalized;
		this->typeSize = typeSize;
	}

	void VertexAttribute::SetPointer(GLuint layoutIndex, GLsizei stride, int pointerOffset)
	{
		glVertexAttribPointer(layoutIndex, size, type, normalized, stride, (void*)pointerOffset);
	}

	void VertexAttribute::EnableAttribArray(GLuint layoutIndex)
	{
		glEnableVertexAttribArray(layoutIndex);
	}
}
