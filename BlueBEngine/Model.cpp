#include "Model.h"

namespace BBB
{
	void Model::SetModelMatrixName(string uniformName)
	{
		m_modelMat.SetUniformName(uniformName);
	}

	void Model::Draw(glm::mat4x4 modelMat)
	{
		// update model mat
		m_modelMat.SetUniformValue(&modelMat, sizeof(modelMat));

		// use shader
		p_shader->UseShader();
		// apply uniforms
		m_modelMat.ApplyUniform(p_shader->GetShader());
		//apply textures as uniforms
		BindTextures();
		p_mesh->Draw(p_shader->GetShader());
	}

	void Model::BindTextures()
	{
		for (int i = 0; i < textures.GetSize(); i++)
		{
			auto texture = textures.GetValue(i);
			texture->SetActiveTexture(i);
			texture->ApplyUniform(p_shader->GetShader());
			texture->Bind(i);
		}
		glActiveTexture(GL_TEXTURE0);
	}
}
