#pragma once
#include "Graphics.h"

namespace BBB
{
	class Application;
	class AppWindow
	{
		GLFWwindow* m_window = nullptr;

	public:
		AppWindow();

		int InitWindow(int width, int height, const char* windowTitle);

		friend Application;
	};

	namespace WindowCallbacks
	{
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	}
}