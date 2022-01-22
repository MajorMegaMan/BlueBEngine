#pragma once
#include "Graphics.h"

namespace BBB
{
	namespace WindowCallbacks
	{
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		void empty_resize_callback(int width, int height);
	}

	class Application;
	class AppWindow
	{
		GLFWwindow* m_window = nullptr;
		int m_width;
		int m_height;

		friend void WindowCallbacks::framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void InternalResizeCallBack(int width, int height);

	public:
		typedef void (*ResizeCallback)(int width, int height);
	private:
		ResizeCallback m_resizeCallback = &WindowCallbacks::empty_resize_callback;

	public:
		AppWindow();

		int InitWindow(int width, int height, const char* windowTitle);
		float GetWidth() const;
		float GetHeight() const;

		void SetResizeCallback(ResizeCallback callback);

		bool TestKey(int key);

		friend Application;
	};
}