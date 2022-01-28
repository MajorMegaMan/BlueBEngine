#include "UniformVar.h"

namespace BBB
{
	void UniformVar::SetUniformName(const string& name)
	{
		uniformName = name;
	}

	void UniformVar::SetUniformSize(size_t byteSize)
	{
		m_byteSize = byteSize;
	}

	size_t UniformVar::GetSize() const
	{
		return m_byteSize;
	}

	void UniformVar::ApplyUniform(GLHandles::ShaderProgram& shader, void* data)
	{
		int location = shader.GetUniformLocation(uniformName.c_str());
		SetUniformFromLocation(location, data);
	}
}
