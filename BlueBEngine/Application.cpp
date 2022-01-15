#include "Application.h"

namespace BBB
{
	Application::Application()
	{
		m_AppWindow.InitWindow(800, 600, "BlueBWindow");
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
}
