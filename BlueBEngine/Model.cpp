#include "Model.h"

namespace BBB
{
	void Model::SetModelMatrixName(string uniformName)
	{
		m_modelMat.SetUniformName(uniformName);
	}

	void Model::Draw(glm::mat4x4 modelMat)
	{
		// use shader
		m_material.UseMaterial();
		// apply uniforms
		m_modelMat.ApplyUniform(m_material.GetShader()->GetShader(), &modelMat);
		//apply textures as uniforms
		BindTextures();
		p_mesh->Draw(m_material.GetShader()->GetShader());
	}

	void Model::BindTextures()
	{
		for (int i = 0; i < textures.GetSize(); i++)
		{
			auto texture = textures.GetValue(i);
			texture->SetActiveTexture(i);
			texture->ApplyUniform(m_material.GetShader()->GetShader(), &i);
			texture->Bind(i);
		}
		glActiveTexture(GL_TEXTURE0);
	}
}
