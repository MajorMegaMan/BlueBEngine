#include "Application.h"
#include "Debug.h"
#include "KeyCallbacks.h"

namespace BBB
{
	Application::Application()
	{
		m_AppWindow.InitWindow(800, 600, "BlueBWindow");

		// Initialise input
		Input::init_key_actions();
		SetKeyInputs();
		glfwSetKeyCallback(m_AppWindow.m_window, AppCallbacks::key_callback);

		// Set Clear colour
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	}

	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::Run()
	{
		Init();
		while (!glfwWindowShouldClose(m_AppWindow.m_window))
		{
			Render();

			glfwSwapBuffers(m_AppWindow.m_window);
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

	// Set the key input callbacks
	void Application::SetKeyInputs()
	{
		// escape to close the program
		Input::set_key_action(Input::ESCAPE, escape_key_action);
	}

	void Application::Update()
	{

	}

	void Application::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	namespace AppCallbacks
	{
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Input::invoke_key_action(window, key, scancode, action, mods);
		}
	}
}
