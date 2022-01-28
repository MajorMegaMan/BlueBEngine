#include "Shader.h"

namespace BBB
{
	void Shader::LoadShader(string vertexFileName, string fragmentFileName)
	{
		m_shader.LoadShaderProgram(vertexFileName.c_str(), fragmentFileName.c_str());
	}

	GLHandles::ShaderProgram& Shader::GetShader()
	{
		return m_shader;
	}

	void Shader::DeleteShader()
	{
		m_shader.DeleteShaderProgram();
	}

	void Shader::SetLayout(VertexAttribute* attributes, int size)
	{
		m_layout.Init(attributes, size);
		m_layout.CalculateStride();
	}

	VertexLayout& Shader::GetLayout()
	{
		return m_layout;
	}

	void Shader::EnableLayout()
	{
		m_layout.SetAttribPointers();
		m_layout.Enable();
	}

	void Shader::ReserveUniformSize(int size)
	{
		m_uniforms.Reserve(size);

		for (int i = 0; i < size; i++)
		{
			m_uniforms.PushBack(nullptr);
		}
	}

	void Shader::SetUniformTarget(int index, UniformVar* target)
	{
		m_uniforms.GetArray()[index] = target;
	}

	void Shader::SetTextureCount(int count)
	{
		m_textureCount = count;
	}

	int Shader::GetTextureCount() const
	{
		return m_textureCount;
	}

	// uses the shader and updates it's uniforms
	void Shader::UseShader()
	{
		m_shader.UseShaderProgram();
	}
}
