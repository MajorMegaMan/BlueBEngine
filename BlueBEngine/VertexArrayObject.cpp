#include "VertexArrayObject.h"

namespace BBB
{
	namespace GLVertex
	{
		void VertexArrayObject::GenArrays()
		{
			glGenVertexArrays(1, &VAO);
		}

		void VertexArrayObject::Bind()
		{
			glBindVertexArray(VAO);
		}

		void VertexArrayObject::DeleteArrays()
		{
			glDeleteVertexArrays(1, &VAO);
		}
	}
}