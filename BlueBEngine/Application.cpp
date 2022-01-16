#include "Application.h"
#include "Debug.h"
#include "KeyCallbacks.h"

namespace BBB
{
	Application::Application()
	{
		m_AppWindow.InitWindow(800, 600, "BlueBWindow");

		Input::init_key_actions();
		SetKeyInputs();
		glfwSetKeyCallback(m_AppWindow.m_window, AppCallbacks::key_callback);
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_AppWindow.m_window))
		{
			glfwSwapBuffers(m_AppWindow.m_window);
			glfwPollEvents();
		}
		glfwTerminate();
	}

	// Set the key input callbacks
	void Application::SetKeyInputs()
	{
		// escape to close the program
		Input::set_key_action(Input::ESCAPE, escape_key_action);
	}

	namespace AppCallbacks
	{
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Input::invoke_key_action(window, key, scancode, action, mods);
		}
	}
}
