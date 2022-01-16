#pragma once
#include "Input.h"

namespace BBB
{
	void escape_key_action(GLFWwindow* window, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}
}