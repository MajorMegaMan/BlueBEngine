#pragma once
#include "Shader.h"
#include "UniformValue.h"

namespace BBB
{
	class Material
	{
		Shader* p_shader;

		DynamicArray<UniformValue> m_uniformValues;

	public:
		void SetShader(Shader& shader);
		Shader* GetShader();

		// This uses the shader and updates the uniform variables from this material.
		void UseMaterial();

		UniformValue* GetUniform(int index);

	private:
		void AllocateUniforms();

		void UpdateUniforms();
	};
}