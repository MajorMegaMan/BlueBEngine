#pragma once
#include "AppWindow.h"
#include "IndexedMesh.h"
#include "ShaderProgram.h"
#include "VertexContainer.h"
#include "Texture2D.h"
#include "Transform.h"
#include "Camera2D.h"

namespace BBB
{
	class Application
	{
		AppWindow m_appWindow;

	public:

		Application();
		~Application();

		void Run();

	protected:
		// Exposed init for user to add their own methods
		virtual void Init();

		virtual void Close();

		virtual void Update();
		virtual void Render();

		// this can be overridden for user inputs
		virtual void SetKeyInputs();

	public:
		virtual void OnMouseClick(int button);
		virtual void OnMouseRelease(int button);

	protected:
		// Window access
		bool TestKey(int key);
		void SetWindowResizeCallback(AppWindow::ResizeCallback callback);
		void GetCursorPos(double& x, double& y);
	};

	namespace AppCallbacks
	{
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void scroll_callback(GLFWwindow* window, double x, double y);

		void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	}
}