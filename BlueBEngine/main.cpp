#include "TestApplication.h"
#include "Debug.h"
using namespace BBB;

int main()
{
	{
		TestApplication application;
		application.Run();
	}
	// Calling glfw Terminate after the application is destructed so that all classes inside the application will safely call their own destructors before the program exits
	glfwTerminate();
	return 0;
}