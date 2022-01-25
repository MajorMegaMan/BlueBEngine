#include "Application.h"
#include "Debug.h"
#include "KeyCallbacks.h"

namespace BBB
{
	Application::Application()
	{
		m_appWindow.InitWindow(800, 600, "BlueBWindow");

		// Initialise input
		Input::init_key_actions();
		SetKeyInputs();
		
		// Set user pointer to this app
		glfwSetWindowUserPointer(m_appWindow.m_window, (void*)this);

		glfwSetKeyCallback(m_appWindow.m_window, AppCallbacks::key_callback);
		glfwSetScrollCallback(m_appWindow.m_window, AppCallbacks::scroll_callback);
		glfwSetMouseButtonCallback(m_appWindow.m_window, AppCallbacks::mouse_callback);

		// Set Clear colour
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		Texture2D::SetImageFlipVertical(true);
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		Init();
		while (!glfwWindowShouldClose(m_appWindow.m_window))
		{
			Update();
			Render();

			glfwSwapBuffers(m_appWindow.m_window);
			glfwPollEvents();
		}
		Close();
	}

	void Application::Init()
	{

	}

	void Application::Close()
	{

	}

	void Application::Update()
	{

	}

	void Application::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	// Set the key input callbacks
	void Application::SetKeyInputs()
	{
		// escape to close the program
		Input::set_key_action(Input::ESCAPE, escape_key_action);
	}

	void Application::OnMouseClick(int button)
	{

	}

	void Application::OnMouseRelease(int button)
	{

	}

	bool Application::TestKey(int key)
	{
		return m_appWindow.TestKey(key);
	}

	void Application::SetWindowResizeCallback(AppWindow::ResizeCallback callback)
	{
		m_appWindow.SetResizeCallback(callback);
	}

	void Application::GetCursorPos(double& x, double& y)
	{
		m_appWindow.GetCursorPos(x, y);
	}

	namespace AppCallbacks
	{
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Input::invoke_key_action(window, key, scancode, action, mods);
		}

		void scroll_callback(GLFWwindow* window, double x, double y)
		{
			Input::invoke_scroll_action(window, x, y);
		}

		void mouse_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Application* app = (Application*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				app->OnMouseClick(button);
				break;
			}
			case GLFW_RELEASE:
			{
				app->OnMouseRelease(button);
				break;
			}
			}
		}
	}
}
