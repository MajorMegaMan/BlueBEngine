#include "TestApplication.h"

void TestApplication::Init()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	m_testMesh.SetVertices(vertices, 9);
	m_testMesh.VertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
}

void TestApplication::Close()
{

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
	m_testMesh.Draw(3);
}
