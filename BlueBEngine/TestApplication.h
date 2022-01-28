#pragma once
#include "Application.h"
#include "LineRenderer.h"
#include "Model.h"

using namespace BBB;

class TestApplication : public Application
{
	Transform m_testTransform;
	Model m_testModel;
	// a model needs
	Shader m_shaderStuff;

	Texture2D m_testTexture;
	Texture2D m_smileTexture;

	// this is a mesh
	IndexedMesh m_testMesh;

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

	void SetupModel();

	void SetUpShader();

	void SetUpMesh(VertexLayout& layout);

	void GenerateMesh();

	void InitialiseLayouts();

	void SetVertices(VertexContainer& container, VertexLayout& layout);

	void LoadTextures();
};

void SetCallbackCamera(Camera2D& cam);

void WindowResize(int width, int height);

void ScrollCallback(GLFWwindow* window, double x, double y);