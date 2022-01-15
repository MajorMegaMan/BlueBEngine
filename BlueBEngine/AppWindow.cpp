#include "AppWindow.h"
#include "Debug.h"

namespace BBB
{
	AppWindow::AppWindow()
	{

	}

	int AppWindow::InitWindow(int width, int height, const char* windowTitle)
	{
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // Create the window
        m_window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
        if (m_window == NULL)
        {
            Debug_PrintLine("Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(m_window);

        // load glad to OS specific values
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            Debug_PrintLine("Failed to initialize GLAD");
            return -1;
        }

        // Set the view port of the window to the size of the window
        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(m_window, WindowCallbacks::framebuffer_size_callback);


        return 0;
	}

    namespace WindowCallbacks
    {
        void framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
    }
}
