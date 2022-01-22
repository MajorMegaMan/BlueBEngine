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

	Transform m_testTransform;
	Camera2D m_camera;

	float lastTime = 0.0f;
	float deltaTime = 0.0f;

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

void SetCallbackCamera(Camera2D& cam);

void WindowResize(int width, int height);

void ScrollCallback(GLFWwindow* window, double x, double y);