#pragma once
#include "IndexedMesh.h"
#include "Shader.h"
#include "Maths.h"
#include "UniformVarHelpers.h"

namespace BBB
{
	class Model
	{
		UniformMat4x4Helper m_modelMat;

	public:
		Shader* p_shader = nullptr;
		Mesh* p_mesh = nullptr;

		DynamicArray<Texture2D*> textures;

		void SetModelMatrixName(string uniformName);

		void Draw(glm::mat4x4 modelMat);

	private:
		void BindTextures();
	};
}