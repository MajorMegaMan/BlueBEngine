#pragma once
#include "Graphics.h"

// This is a struct that contains all the neccesary information for an attribute that is used in a shader.

namespace BBB
{
	struct VertexAttibute
	{
		GLint size = 0;
		GLenum type = 0;
		GLboolean normalized = 0;
		GLsizei typeSize = 0;

	public:
		void SetValues(GLint size, GLenum type, GLboolean normalized, GLsizei typeSize);

		void SetPointer(GLuint layoutIndex, GLsizei stride, int pointerOffset);

		static void EnableAttribArray(GLuint layoutIndex);
	};
}