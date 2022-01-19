#include "TestApplication.h"
#include "Debug.h"

void TestApplication::Init()
{
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	GenerateMesh();
	// Apply vertices to mesh

	// Create Layout attributes
	InitialiseLayouts();

	// Create container to convert Layouts to be used in shader
	VertexContainer container;	
	SetLayoutData(container);

	// Send the container variables to the mesh
	container.ApplyToMesh(m_testMesh);

	// apply indices to mesh
	// must applya directly after SetVertices as this does not conatin another Rebind of the desired VAO
	m_testMesh.SetIndices(indices, 6);

	m_vertexLayout.SetAttribPointers();
	m_vertexLayout.Enable();
}

void TestApplication::Close()
{
	m_testMesh.Delete();
}

void TestApplication::SetKeyInputs()
{
	Application::SetKeyInputs();
}

void TestApplication::Update()
{

}

void TestApplication::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_shader.UseShaderProgram();
	m_testMesh.IDraw(6, GL_UNSIGNED_INT);
}

void TestApplication::GenerateMesh()
{
	m_testMesh.Generate();
}

void TestApplication::InitialiseLayouts()
{
	// Create Layout attributes
	m_vertexLayout.Init(1);
	auto vec3Attrib = m_vertexLayout.GetBegin();
	// Vec3 attrib position
	vec3Attrib->SetValues(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
}

void TestApplication::SetLayoutData(VertexContainer& container)
{
	// positions
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};

	// initialise vertices with layouts
	container.Init(m_vertexLayout, 4);

	// Set positions attribute in container
	for (int i = 0; i < 4; i++)
	{
		container.SetVertex(i, 0, vertices + (i * 3));
	}
}
