#pragma once
#include "Application.h"
#include "LineRenderer.h"

using namespace BBB;

class TestApplication : public Application
{
	Transform m_testTransform;
	// a model needs
	ShaderProgram m_shader;
	VertexLayout m_vertexLayout;
	IndexedMesh m_testMesh;
	Texture2D m_testTexture;
	Texture2D m_smileTexture;

	Camera2D m_camera;

	LineRenderer lines;
	LineRenderer followMouse;

	bool isAdding = false;
	glm::vec2 lastAdded = { 0.0f, 0.0f };

	glm::vec2 mousePos;

	float lastTime = 0.0f;
	float deltaTime = 0.0f;

public:
	TestApplication();

	void Init() override;

	void Close() override;

	void SetKeyInputs() override;

	void Update() override;

	void Render() override;

	// Inputs
	void OnMouseClick(int button) override;
	void OnMouseRelease(int button) override;

	// Debugging shit
	void DrawCircle(glm::vec2 centre, float size, int segmentCount);

	void GenerateMesh();

	void InitialiseLayouts();

	void SetLayoutData(VertexContainer& container);
};

void SetCallbackCamera(Camera2D& cam);

void WindowResize(int width, int height);

void ScrollCallback(GLFWwindow* window, double x, double y);