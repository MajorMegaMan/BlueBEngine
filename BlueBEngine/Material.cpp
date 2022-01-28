#include "Material.h"

namespace BBB
{
	void Material::SetShader(Shader& shader)
	{
		p_shader = &shader;
		AllocateUniforms();
	}

	Shader* Material::GetShader()
	{
		return p_shader;
	}

	void Material::UseMaterial()
	{
		p_shader->UseShader();
		UpdateUniforms();
	}

	UniformValue* Material::GetUniform(int index)
	{
		return &m_uniformValues.GetValue(index);
	}

	void Material::AllocateUniforms()
	{
		m_uniformValues.Clear();
		int uniformCount = p_shader->m_uniforms.GetSize();
		m_uniformValues.Reserve(uniformCount);
		for (int i = 0; i < uniformCount; i++)
		{
			UniformVar* uniform = p_shader->m_uniforms.GetValue(i);
			m_uniformValues.PushBack(UniformValue(uniform->GetSize()));
		}
	}

	void Material::UpdateUniforms()
	{
		for (int i = 0; i < m_uniformValues.GetSize(); i++)
		{
			UniformVar* uniform = p_shader->m_uniforms.GetValue(i);
			m_uniformValues.GetValue(i).ApplyValue(p_shader->GetShader(), *uniform);
		}
	}
}

