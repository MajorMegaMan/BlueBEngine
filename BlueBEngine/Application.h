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
	};
}