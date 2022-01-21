#pragma once
#include "AppWindow.h"
#include "IndexedMesh.h"
#include "ShaderProgram.h"
#include "VertexContainer.h"
#include "Texture2D.h"
#include "Transform.h"

namespace BBB
{
	class Application
	{
		AppWindow m_AppWindow;

	public:

		Application();
		~Application();

		void Run();

	protected:
		// Exposed init for user to add their own methods
		virtual void Init();

		virtual void Close();

		// this can be overridden for user inputs
		virtual void SetKeyInputs();

		virtual void Update();

		virtual void Render();
	};

	namespace AppCallbacks
	{
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	}
}