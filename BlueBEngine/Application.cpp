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
		glfwSetKeyCallback(m_appWindow.m_window, AppCallbacks::key_callback);
		glfwSetScrollCallback(m_appWindow.m_window, AppCallbacks::scroll_callback);

		// Set Clear colour
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		Texture2D::SetImageFlipVertical(true);
	}

	Application::~Application()
	{
		glfwTerminate();
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
		glfwTerminate();
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

	bool Application::TestKey(int key)
	{
		return m_appWindow.TestKey(key);
	}

	void Application::SetWindowResizeCallback(AppWindow::ResizeCallback callback)
	{
		m_appWindow.SetResizeCallback(callback);
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
	}
}
