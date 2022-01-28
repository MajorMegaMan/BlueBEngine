#include "TestApplication.h"
#include "Debug.h"
#include "Input.h"

#define TEST_VERT_FILE "basic.vert"
#define TEST_FRAG_FILE "basic.frag"
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

	LoadTextures();

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

void TestApplication::Update()
{
	float time = glfwGetTime();
	deltaTime = time - lastTime;
	lastTime = time;

	double mouseX, mouseY;
	GetCursorPos(mouseX, mouseY);
	mousePos.x = mouseX;
	mousePos.y = mouseY;

	auto camMat = m_camera.FindOrthoMatrix();
	glm::vec4 mousething(mousePos.x, mousePos.y, 0.0f, 1.0f);
	mousething = glm::inverse(camMat) * mousething;

	mousePos = { mousething.x, mousething.y };

	float camSpeed = deltaTime * CAM_MOVE_SPEED * m_camera.GetCamHeight();

	m_testTransform.Rotate(deltaTime * 90, { 0.0f, 0.0f, 1.0f });

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

	if (isAdding)
	{
		followMouse.Clear();
		followMouse.AddLine(lastAdded, mousePos);
	}

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
			DrawCircle(mousePos, 0.05f, 32);
		}
	}

	if (button == 1)
	{
		isAdding = !isAdding;
		lastAdded = mousePos;
		followMouse.Clear();
	}
}

void TestApplication::OnMouseRelease(int button)
{

}

void TestApplication::DrawCircle(glm::vec2 centre, float size, int segmentCount)
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

	m_testModel.textures.Reserve(2);
	m_testModel.textures.PushBack(&m_testTexture);
	m_testModel.textures.PushBack(&m_smileTexture);
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

	// Create container to convert Layouts to be used in shader
	SetVertices(m_testMesh.vertices, layout);

	// Send the container variables to the mesh
	m_testMesh.ApplyVertices();

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// apply indices to mesh
	// must apply directly after SetVertices as this does not conatin another Rebind of the desired VAO
	m_testMesh.SetIndices(indices, 6);
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
	VertexAttribute layouts[3];
	
	// Vec3 attrib position
	layouts[0].SetValues(3, GL_FLOAT, GL_FALSE, sizeof(float));

	// Vec3 attrib colour
	layouts[1].SetValues(3, GL_FLOAT, GL_FALSE, sizeof(float));

	// Vec2 attrib texture UVs
	layouts[2].SetValues(2, GL_FLOAT, GL_FALSE, sizeof(float));

	//m_vertexLayout.CalculateStride();
	m_shaderStuff.SetLayout(layouts, 3);
}

void TestApplication::SetVertices(VertexContainer& container, VertexLayout& layout)
{
	// positions
	glm::vec3 vertices[] = {
	{ 0.5f,  0.5f, 0.0f},  // top right
	{ 0.5f, -0.5f, 0.0f},  // bottom right
	{-0.5f, -0.5f, 0.0f},  // bottom left
	{-0.5f,  0.5f, 0.0f}   // top left 
	};

	// colours
	glm::vec3 colours[] = {
	 {1.0f,  0.0f, 0.0f},  // top right
	 {0.0f,  1.0f, 0.0f},  // bottom right
	 {0.0f,  0.0f, 1.0f},  // bottom left
	 {1.0f,  0.0f, 1.0f}   // top left 
	};

	glm::vec2 UVs[] = {
	{1.0f,  1.0f},  // top right
	{1.0f,  0.0f},  // bottom right
	{0.0f,  0.0f},  // bottom left
	{0.0f,  1.0f}   // top left 
	};

	// initialise vertices with layouts
	container.Init(layout, 4);

	// Set positions attribute in container
	for (int i = 0; i < 4; i++)
	{
		container.SetVertex(i, 0, vertices + i);
	}

	// Set colours attribute in container
	for (int i = 0; i < 4; i++)
	{
		container.SetVertex(i, 1, colours + i);
	}

	// Set colours attribute in container
	for (int i = 0; i < 4; i++)
	{
		container.SetVertex(i, 2, UVs + i);
	}
}

void TestApplication::LoadTextures()
{
	m_testTexture.LoadImage("container.jpg");
	m_smileTexture.LoadImage("awesomeface.png");

	m_testTexture.SetUniformName("texture1");
	m_smileTexture.SetUniformName("texture2");
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
