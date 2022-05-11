#include "TestApplication.h"
#include "Debug.h"
#include "Input.h"

#define TEST_VERT_FILE "unlitShape.vert"
#define TEST_FRAG_FILE "unlitShape.frag"
#define TEST_UNIFORM_FRAG "uniformTest.frag"

#define CAM_HEIGHT 10.0f
#define CAM_MOVE_SPEED 1.0f
#define CAM_ZOOM_MAG 2.0f

TestApplication::TestApplication()
{
	LineRenderer::InitialiseShader();
}

void TestApplication::Init()
{
	SetCallbackCamera(m_camera);
	SetWindowResizeCallback(WindowResize);
	Input::set_scroll_action(ScrollCallback);

	SetupModel();
	SetUpShader();
	SetUpMesh(m_shaderStuff.GetLayout());

	m_camera.SetCamHeight(CAM_HEIGHT);

	lines.SetColour({ 1.0f, 0.0f, 0.0f, 1.0f });
}

void TestApplication::Close()
{
	LineRenderer::DeleteShader();
}

void TestApplication::SetKeyInputs()
{
	Application::SetKeyInputs();
}

bool spaceDown = false;

void TestApplication::Update(float deltaTime)
{
	double mouseX, mouseY;
	GetCursorPos(mouseX, mouseY);
	mousePos.x = mouseX;
	mousePos.y = mouseY;

	auto camMat = m_camera.FindOrthoMatrix();
	glm::vec4 mousething(mousePos.x, mousePos.y, 0.0f, 1.0f);
	mousething = glm::inverse(camMat) * mousething;

	mousePos = { mousething.x, mousething.y };

	float camSpeed = deltaTime * CAM_MOVE_SPEED * m_camera.GetCamHeight();

	//m_testTransform.Rotate(deltaTime * 90, { 0.0f, 0.0f, 1.0f });

	if (TestKey(GLFW_KEY_W))
	{
		m_camera.Translate({ 0.0f, camSpeed, 0.0f });
	}
	if (TestKey(GLFW_KEY_S))
	{
		m_camera.Translate({ 0.0f, -camSpeed, 0.0f });
	}
	if (TestKey(GLFW_KEY_D))
	{
		m_camera.Translate({ camSpeed, 0.0f, 0.0f });
	}
	if (TestKey(GLFW_KEY_A))
	{
		m_camera.Translate({ -camSpeed, 0.0f, 0.0f });
	}
	if (TestKey(GLFW_KEY_SPACE))
	{
		if (!spaceDown)
		{
			spaceDown = true;
			glm::vec4 colour = lines.GetColour();
			colour.x = 1.0f - colour.x;
			colour.y = 1.0f - colour.y;
			colour.z = 1.0f - colour.z;
			lines.SetColour(colour);
		}
	}
	else
	{
		spaceDown = false;
	}
}

void TestApplication::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	auto camMat = m_camera.FindOrthoMatrix();

	auto mat = m_testTransform.CalcMatrix();
	mat = camMat * mat;

	m_testModel.Draw(mat);

	followMouse.Clear();
	if (isAdding)
	{
		followMouse.AddLine(lastAdded, mousePos);
	}

	DrawCircle(followMouse, mousePos, 0.05f, 32);

	int triSize = 0;
	auto triangles = triRenders.GetTriArray(triSize);

	if (triSize > 0)
	{
		for (int i = 0; i < triSize; i++)
		{
			if (triangles[i].PointInTriangle({ mousePos.x, mousePos.y, 0.0f }))
			{
				triRenders.SetTriangleColour(i, { 1.0f, 0.0f, 0.0f, 0.0f });
			}
			else
			{
				triRenders.SetTriangleColour(i, { 0.0f, 1.0f, 0.0f, 0.0f });
			}
		}
		triRenders.ApplyVertices();
	}

	triRenders.Draw(camMat);
	lines.Draw(camMat);
	followMouse.Draw(camMat);
}

void TestApplication::OnMouseClick(int button)
{
	if (button == 0)
	{
		if (isAdding)
		{
			lines.AddLine(lastAdded, mousePos);
			lastAdded = mousePos;
		}
		else
		{
			DrawCircle(lines, mousePos, 0.05f, 32);
		}

		points.PushBack(mousePos);
		if (points.GetSize() > 2)
		{
			float startTime = glfwGetTime();
			m_delMap.Clear();
			m_delMap.Init((Vector2*)points.GetArray(), points.GetSize());
			float delMapTime = glfwGetTime() - startTime;
			Debug_Print("DelMapTime: ");
			Debug_PrintLine(std::to_string(delMapTime));
			

			float drawInitStart = glfwGetTime();
			int triCount = m_delMap.GetTriCount();
			auto triArray = m_delMap.GetTriBegin();
			for (int i = 0; i < triCount; i++)
			{
				Triangle tri;
				for (int j = 0; j < 3; j++)
				{
					const DelPoint* pos = triArray[i].GetPoint(j);
					tri.positions[j] = {pos->x, pos->y, 0.0f};
				}
				tri.colour = { 0.0f, 1.0f, 0.0f, 0.0f };
				triRenders.AddTriangle(tri);
			}
			triRenders.UpdateTriangles();
			triRenders.ApplyVertices();
			Debug_Print("TriSetTime: ");
			float initTime = glfwGetTime() - drawInitStart;
			Debug_PrintLine(std::to_string(initTime));
			Debug_EndLine();
		}
	}

	if (button == 1)
	{
		isAdding = !isAdding;
		lastAdded = mousePos;
		followMouse.Clear();

		points.Clear();
		m_delMap.Clear();
		triRenders.ClearTriangles();
	}
}

void TestApplication::OnMouseRelease(int button)
{

}

void TestApplication::DrawCircle(LineRenderer& lines, glm::vec2 centre, float size, int segmentCount)
{
	float cosAngle = cos(2 * 3.14159f / segmentCount);
	float sinAngle = sin(2 * 3.14159f / segmentCount);

	glm::mat2 rotMat = { {cosAngle, -sinAngle},{sinAngle, cosAngle} };

	glm::vec2 plotPoint(0, size);

	for (int i = 0; i <= segmentCount; i++)
	{
		auto start = centre + plotPoint;
		plotPoint = rotMat * plotPoint;
		auto end = centre + plotPoint;
		lines.AddLine(start, end);
	}
}

void TestApplication::SetupModel()
{
	m_testModel.p_mesh = &m_testMesh;
	m_testModel.m_material.SetShader(m_shaderStuff);
	
	m_testModel.SetModelMatrixName("transform");
}

void TestApplication::SetUpShader()
{
	// Load the shader programs
	m_shaderStuff.LoadShader(TEST_VERT_FILE, TEST_FRAG_FILE);

	// Create Layout attributes
	InitialiseLayouts();

	// Set Uniform pointers
	//m_shaderStuff.ReserveUniformSize(1);
	//m_shaderStuff.SetUniformTarget(0, &m_MVPUniform);

	// Set value of uniforms
	//m_MVPUniform.SetUniformName("transform");

	// Set Texture count
	m_shaderStuff.SetTextureCount(2);
}

void TestApplication::SetUpMesh(VertexLayout& layout)
{
	GenerateMesh();
	// Apply vertices to mesh
	m_testMesh.SetUsage(GL_DYNAMIC_DRAW);
	// Create container to convert Layouts to be used in shader
	SetVertices(m_testMesh.vertices, layout);

	// Send the container variables to the mesh
	m_testMesh.ApplyVertices();
	// must apply directly after SetVertices as this does not conatin another Rebind of the desired VAO
	m_testMesh.ApplyIndices();

	//m_shaderStuff.EnableLayout();
	// Set pointers of currently bound vbo
	layout.SetAttribPointers();
	// enable attributes
	layout.Enable();
}

void TestApplication::GenerateMesh()
{
	m_testMesh.Generate();
}

void TestApplication::InitialiseLayouts()
{
	// Create Layout attributes
	VertexAttribute layouts[2];
	
	// Vec3 attrib position
	layouts[0].SetValues(3, GL_FLOAT, GL_FALSE, sizeof(float));

	// Vec3 attrib colour
	layouts[1].SetValues(3, GL_FLOAT, GL_FALSE, sizeof(float));

	//m_vertexLayout.CalculateStride();
	m_shaderStuff.SetLayout(layouts, 2);
}

void TestApplication::SetVertices(VertexContainer& container, VertexLayout& layout)
{
	//InitialiseIndexedQuad(m_testMesh, layout);

	glm::vec3 positions[] = {
	 {0.0f,  1.0f, 0.0f},
	 {1.0f,  -1.0f, 0.0f},
	 {-1.0f,  -1.0f, 0.0f}
	};

	InitialiseIndexedTriWithCentre(positions, m_testMesh, layout);

	// colours
	glm::vec4 colours[] = {
	 {1.0f,  0.0f, 0.0f, 1.0f},  // top right
	 {0.0f,  1.0f, 0.0f, 1.0f},  // bottom right
	 {0.0f,  0.0f, 1.0f, 1.0f},  // bottom left
	 {1.0f,  0.0f, 1.0f, 1.0f}   // top left 
	};

	// Set colours attribute in container
	for (int i = 0; i < 4; i++)
	{
		container.SetVertex(i, 1, colours + i);
	}
}

Camera2D* callbackCamera;

void SetCallbackCamera(Camera2D& cam)
{
	callbackCamera = &cam;
}

void WindowResize(int width, int height)
{
	callbackCamera->aspectRatio = (float)width / (float)height;
}

void ScrollCallback(GLFWwindow* window, double x, double y)
{
	float camZoom = (callbackCamera->GetCamHeight() / CAM_ZOOM_MAG) * -y;
	callbackCamera->Translate({ 0.0f,0.0f, camZoom });
}
