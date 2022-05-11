#pragma once
#include "Application.h"
#include "LineRenderer.h"
#include "Model.h"
#include "Geometry.h"
#include "TriangleRenderer.h"
#include "Voronoi/DelaunayMap.h"

using namespace BBB;

class TestApplication : public Application
{
	Transform m_testTransform;
	Model m_testModel;
	// a model needs
	Shader m_shaderStuff;

	// this is a mesh
	IndexedMesh m_testMesh;

	DelaunayMap m_delMap;

	Camera2D m_camera;

	DynamicArray<glm::vec2> points;

	LineRenderer lines;
	LineRenderer followMouse;
	TriangleRender triRenders;

	bool isAdding = false;
	glm::vec2 lastAdded = { 0.0f, 0.0f };

	glm::vec2 mousePos;

public:
	TestApplication();

	void Init() override;

	void Close() override;

	void SetKeyInputs() override;

	void Update(float deltaTime) override;

	void Render() override;

	// Inputs
	void OnMouseClick(int button) override;
	void OnMouseRelease(int button) override;

	// Debugging shit
	void DrawCircle(LineRenderer& lines, glm::vec2 centre, float size, int segmentCount);

	void SetupModel();

	void SetUpShader();

	void SetUpMesh(VertexLayout& layout);

	void GenerateMesh();

	void InitialiseLayouts();

	void SetVertices(VertexContainer& container, VertexLayout& layout);
};

void SetCallbackCamera(Camera2D& cam);

void WindowResize(int width, int height);

void ScrollCallback(GLFWwindow* window, double x, double y);