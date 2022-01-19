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
		GLsizei stride = 0;

	public:
		void SetValues(GLint size, GLenum type, GLboolean normalized, GLsizei stride);

		void SetPointer(GLuint layoutIndex, int pointerOffset);

		static void EnableAttribArray(GLuint layoutIndex);
	};
}