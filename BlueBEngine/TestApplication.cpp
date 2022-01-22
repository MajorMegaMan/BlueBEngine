#include "TestApplication.h"
#include "Debug.h"
#include "Input.h"

#define TEST_VERT_FILE "basic.vert"
#define TEST_FRAG_FILE "basic.frag"
#define TEST_UNIFORM_FRAG "uniformTest.frag"

#define CAM_MOVE_SPEED 5.0f
#define CAM_ZOOM_MAG 2.0f

TestApplication::TestApplication() : m_shader(TEST_VERT_FILE, TEST_FRAG_FILE)
{
	
}

void TestApplication::Init()
{
	SetCallbackCamera(m_camera);
	SetWindowResizeCallback(WindowResize);
	Input::set_scroll_action(ScrollCallback);

	GenerateMesh();
	// Apply vertices to mesh

	// Create Layout attributes
	InitialiseLayouts();

	// Create container to convert Layouts to be used in shader
	VertexContainer container;
	SetLayoutData(container);

	// Send the container variables to the mesh
	container.ApplyToMesh(m_testMesh);

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// apply indices to mesh
	// must applya directly after SetVertices as this does not conatin another Rebind of the desired VAO
	m_testMesh.SetIndices(indices, 6);

	//glm::vec4 vec4 = { 0.0f, 1.0f, 1.0f, 1.0f };
	//m_shader.SetUniform4f("ourColor", (float*)&vec4);

	m_vertexLayout.SetAttribPointers();
	m_vertexLayout.Enable();

	m_testTexture.LoadImage("container.jpg");
	m_smileTexture.LoadImage("awesomeface.png");

	m_shader.SetUniform1i("texture1", 0);
	m_shader.SetUniform1i("texture2", 1);

	//m_testTransform.Translate({ 0.5f, 0.5f, 0.0f });
	//m_testTransform.Rotate(90, { 1.0f, 0.0f, 0.0f });

	m_camera.SetCamHeight(10.0f);
}

void TestApplication::Close()
{
	m_testMesh.Delete();
	m_testTexture.DeleteTexture();
	m_smileTexture.DeleteTexture();
}

void TestApplication::SetKeyInputs()
{
	Application::SetKeyInputs();
}

void TestApplication::Update()
{
	float time = glfwGetTime();
	deltaTime = time - lastTime;
	lastTime = time;

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
}

void TestApplication::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, -glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 projection;
	//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	//projection = glm::ortho(-800.0f / 2.0f, 800.0f / 2.0f, -600 / 2.0f, 600 / 2.0f, -1.0f, 1.0f);

	projection = m_camera.FindOrthoMatrix();

	auto mat = m_testTransform.CalcMatrix();

	mat = projection * view * mat;

	m_shader.SetUniformMatrix4f("transform", (float*)&mat);

	m_shader.UseShaderProgram();
	m_testTexture.Bind(0);
	m_smileTexture.Bind(1);
	m_testMesh.IDraw(6, GL_UNSIGNED_INT);
}

void TestApplication::GenerateMesh()
{
	m_testMesh.Generate();
}

void TestApplication::InitialiseLayouts()
{
	// Create Layout attributes
	m_vertexLayout.Init(3);
	auto layouts = m_vertexLayout.GetBegin();

	// Vec3 attrib position
	layouts[0].SetValues(3, GL_FLOAT, GL_FALSE, sizeof(float));

	// Vec3 attrib colour
	layouts[1].SetValues(3, GL_FLOAT, GL_FALSE, sizeof(float));

	// Vec2 attrib texture UVs
	layouts[2].SetValues(2, GL_FLOAT, GL_FALSE, sizeof(float));

	m_vertexLayout.CalculateStride();
}

void TestApplication::SetLayoutData(VertexContainer& container)
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
	container.Init(m_vertexLayout, 4);

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
