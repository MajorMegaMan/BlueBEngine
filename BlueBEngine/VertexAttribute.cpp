#include "VertexAttribute.h"

namespace BBB
{
	void VertexAttibute::SetValues(GLint size, GLenum type, GLboolean normalized, GLsizei typeSize)
	{
		this->size = size;
		this->type = type;
		this->normalized = normalized;
		this->typeSize = typeSize;
	}

	void VertexAttibute::SetPointer(GLuint layoutIndex, GLsizei stride, int pointerOffset)
	{
		glVertexAttribPointer(layoutIndex, size, type, normalized, stride, (void*)pointerOffset);
	}

	void VertexAttibute::EnableAttribArray(GLuint layoutIndex)
	{
		glEnableVertexAttribArray(layoutIndex);
	}
}
