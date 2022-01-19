#include "VertexAttribute.h"

namespace BBB
{
	void VertexAttibute::SetValues(GLint size, GLenum type, GLboolean normalized, GLsizei stride)
	{
		this->size = size;
		this->type = type;
		this->normalized = normalized;
		this->stride = stride;
	}

	void VertexAttibute::SetPointer(GLuint layoutIndex, int pointerOffset)
	{
		glVertexAttribPointer(layoutIndex, size, type, normalized, stride, (void*)pointerOffset);
	}

	void VertexAttibute::EnableAttribArray(GLuint layoutIndex)
	{
		glEnableVertexAttribArray(layoutIndex);
	}
}
