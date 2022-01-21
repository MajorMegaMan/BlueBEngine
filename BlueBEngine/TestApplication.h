#pragma once
#include "Application.h"

using namespace BBB;

class TestApplication : public Application
{
	ShaderProgram m_shader;
	IndexedMesh m_testMesh;
	Texture2D m_testTexture;
	Texture2D m_smileTexture;

	VertexLayout m_vertexLayout;

public:
	TestApplication();

	void Init() override;

	void Close() override;

	void SetKeyInputs() override;

	void Update() override;

	void Render() override;

	// Debugging shit
	void GenerateMesh();

	void InitialiseLayouts();

	void SetLayoutData(VertexContainer& container);
};