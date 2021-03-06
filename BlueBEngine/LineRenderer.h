#pragma once
#include "IndexedMesh.h"
#include "Shader.h"
#include "VertexContainer.h"
#include "Maths.h"
#include <Utilities/DynamicArray.h>

using namespace BBB;
using namespace GLHandles;

class LineRenderer
{
	DynamicArray<glm::vec2> m_positions;

	glm::vec4 m_colour;

	Mesh m_mesh;

	typedef void (LineRenderer::* VoidAction)(glm::mat4x4);
	VoidAction m_drawAction = &LineRenderer::Empty;

public:
	LineRenderer();
	~LineRenderer();

	void Draw(glm::mat4x4 MVP);

	void Clear();

	void SetColour(glm::vec4 colour);
	glm::vec4 GetColour() const;

	void AddLine(glm::vec2 start, glm::vec2 end);
	void AddShape(glm::vec2* vertices, int count);

private:
	void AddLineToDrawList(glm::vec2 start, glm::vec2 end);

	void Update();

	void Empty(glm::mat4x4 MVP);

	void UpdateDraw(glm::mat4x4 MVP);

	void ConfimedDraw(glm::mat4x4 MVP);

	void GLDelete();

public:
	// Must be called before using any line renderer as it initialises a singleton shader
	static void InitialiseShader();

	// Must delete the singleton shader before opengl is terminated.
	static void DeleteShader();
};