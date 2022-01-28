#pragma once
#include "ShaderProgram.h"
#include "VertexContainer.h"
#include <Utilities/DynamicArray.h>
#include "UniformVar.h"

namespace BBB
{
	class Material;

	// This class contains all the varibles needed for a shader to function properly
	class Shader
	{
		// This is the actual shader that OpenGL uses
		GLHandles::ShaderProgram m_shader;
		// This is a helper that has the information needed to construct vertex data
		VertexLayout m_layout;

		// This is an array that contains helpers to set uniform variables
		DynamicArray<UniformVar*> m_uniforms;

		int m_textureCount = 0;

	public:
		void LoadShader(string vertexFileName, string fragmentFileName);
		GLHandles::ShaderProgram& GetShader();

		void DeleteShader();

		void SetLayout(VertexAttribute* attributes, int size);
		VertexLayout& GetLayout();

		void EnableLayout();

		void ReserveUniformSize(int size);

		void SetUniformTarget(int index, UniformVar* target);

		void SetTextureCount(int count);
		int GetTextureCount() const;

		void UseShader();

		friend Material;
	};
}