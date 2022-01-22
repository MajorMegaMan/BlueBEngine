#include "AppWindow.h"
#include "Debug.h"

namespace BBB
{
    static AppWindow* _windowInstance = nullptr;

    void AppWindow::InternalResizeCallBack(int width, int height)
    {
        m_width = width;
        m_height = height;
        m_resizeCallback(width, height);
    }

    AppWindow::AppWindow()
	{

	}

	int AppWindow::InitWindow(int width, int height, const char* windowTitle)
	{
        if (_windowInstance != nullptr)
        {
            Debug_PrintLine("Window is already initialised.");
            return -1;
        }
        _windowInstance = this;

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

        m_width = width;
        m_height = height;

        // Set the view port of the window to the size of the window
        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(m_window, WindowCallbacks::framebuffer_size_callback);

        return 0;
	}

    float AppWindow::GetWidth() const
    {
        return m_width;
    }

    float AppWindow::GetHeight() const
    {
        return m_height;
    }

    void AppWindow::SetResizeCallback(ResizeCallback callback)
    {
        m_resizeCallback = callback;
    }

    bool AppWindow::TestKey(int key)
    {
        return glfwGetKey(m_window, key) == GLFW_PRESS;
    }

    namespace WindowCallbacks
    {
        void framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            _windowInstance->InternalResizeCallBack(width, height);
            glViewport(0, 0, width, height);
        }

        void empty_resize_callback(int width, int height)
        {
            // This is intentionally empty
        }
    }
}
