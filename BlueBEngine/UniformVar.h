#pragma once
#include "ShaderProgram.h"
#include "string.h"

namespace BBB
{
	class UniformVar
	{
		string uniformName;
		char* valueBuffer = nullptr;

	protected:
		virtual void SetUniformFromLocation(int location, const void* data) = 0;

	public:

		~UniformVar()
		{
			if (valueBuffer != nullptr)
			{
				delete[] valueBuffer;
				valueBuffer = nullptr;
			}
		}

		void SetUniformName(const string& name)
		{
			uniformName = name;
		}

		void SetUniformValue(void* data, size_t byteSize)
		{
			if (valueBuffer != nullptr)
			{
				delete[] valueBuffer;
			}
			valueBuffer = new char[byteSize];
			memcpy(valueBuffer, data, byteSize);
		}

		// Sets uniform value in the shader without useing the shader first.
		void ApplyUniform(GLHandles::ShaderProgram& shader)
		{
			int location = shader.GetUniformLocation(uniformName.c_str());
			SetUniformFromLocation(location, valueBuffer);
		}
	};
}