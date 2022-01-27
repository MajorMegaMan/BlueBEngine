#include "LineRenderer.h"

Shader _lineShader;

LineRenderer::LineRenderer()
{
	SetColour({ 1.0f, 1.0f, 1.0f, 1.0f });

	m_mesh.Generate();
	m_mesh.SetUsage(GL_DYNAMIC_DRAW);
}

LineRenderer::~LineRenderer()
{
	GLDelete();
}

void LineRenderer::Draw(glm::mat4x4 MVP)
{
	(this->*m_drawAction)(MVP);
}

void LineRenderer::Clear()
{
	m_positions.Clear();
	m_drawAction = &LineRenderer::Empty;
}

void LineRenderer::SetColour(glm::vec4 colour)
{
	m_colour = colour;
}

glm::vec4 LineRenderer::GetColour() const
{
	return m_colour;
}

void LineRenderer::AddLine(glm::vec2 start, glm::vec2 end)
{
	AddLineToDrawList(start, end);
	m_drawAction = &LineRenderer::UpdateDraw;
}

void LineRenderer::AddShape(glm::vec2* vertices, int count)
{
	if (count > 1)
	{
		for (int i = 0; i < count - 1; i++)
		{
			AddLineToDrawList(vertices[i], vertices[i + 1]);
		}
		AddLineToDrawList(vertices[count - 1], vertices[0]);
		m_drawAction = &LineRenderer::UpdateDraw;
	}
}

void LineRenderer::AddLineToDrawList(glm::vec2 start, glm::vec2 end)
{
	m_positions.PushBack(start);
	m_positions.PushBack(end);
}

void LineRenderer::Update()
{
	m_mesh.SetVertices((float*)m_positions.GetArray(), 2 * m_positions.GetSize());
	_lineShader.EnableLayout();
}

void LineRenderer::Empty(glm::mat4x4 MVP)
{
	// This is empty for when a draw call is made, but there are not enoguh vertices for the line renderer to function
}

void LineRenderer::UpdateDraw(glm::mat4x4 MVP)
{
	_lineShader.UseShader();
	_lineShader.GetShader().SetUniformMatrix4f("MVP", (float*)&MVP);
	_lineShader.GetShader().SetUniform4f("colour", (float*)&m_colour);
	m_mesh.Bind();
	Update();

	glDrawArrays(GL_LINES, 0, m_positions.GetSize());

	m_drawAction = &LineRenderer::ConfimedDraw;
}

void LineRenderer::ConfimedDraw(glm::mat4x4 MVP)
{
	_lineShader.UseShader();
	_lineShader.GetShader().SetUniformMatrix4f("MVP", (float*)&MVP);
	_lineShader.GetShader().SetUniform4f("colour", (float*)&m_colour);
	m_mesh.Bind();

	glDrawArrays(GL_LINES, 0, m_positions.GetSize());
}

void LineRenderer::GLDelete()
{
	m_mesh.Delete();
}

void LineRenderer::InitialiseShader()
{
	_lineShader.LoadShader("line.vert", "line.frag");

	VertexAttribute layouts[1];
	layouts[0].SetValues(2, GL_FLOAT, GL_FALSE, sizeof(float));
	_lineShader.SetLayout(layouts, 1);
}

void LineRenderer::DeleteShader()
{
	_lineShader.DeleteShader();
}
