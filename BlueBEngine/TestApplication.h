#pragma once
#include "Application.h"

using namespace BBB;

class TestApplication : public Application
{
	ShaderProgram m_shader;
	Mesh m_testMesh;

	void Init() override;

	void Close() override;

	void SetKeyInputs() override;

	void Update() override;

	void Render() override;
};