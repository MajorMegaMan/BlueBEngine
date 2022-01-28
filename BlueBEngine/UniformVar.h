#pragma once
#include "ShaderProgram.h"
#include "string.h"

namespace BBB
{
	// This is a reference to help get locations to be able to send data to the shader
	class UniformVar
	{
		string uniformName;
		size_t m_byteSize;

	protected:
		virtual void SetUniformFromLocation(int location, const void* data) = 0;

	public:
		// This is the name of the uniform that is used by the shader
		void SetUniformName(const string& name);

		void SetUniformSize(size_t byteSize);
		size_t GetSize() const;

		// Sets uniform value in the shader without useing the shader first.
		void ApplyUniform(GLHandles::ShaderProgram& shader, void* data);
	};
}