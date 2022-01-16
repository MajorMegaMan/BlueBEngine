#pragma once
#include "AppWindow.h"

namespace BBB
{
	class Application
	{
		AppWindow m_AppWindow;

	public:

		Application();

		void Run();

	protected:
		virtual void SetKeyInputs();
	};

	namespace AppCallbacks
	{
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	}
}