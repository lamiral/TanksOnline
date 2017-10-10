#include "Window.h"

Window::Window(int w, int h, const char *title)
{
	glfwInit();

	window = glfwCreateWindow(w, h, title, NULL, NULL);

	if (!window)
	{
		LogOut::log("Error : window is not created");

		return;
	}
}

bool Window::open()
{
	glfwPollEvents();
	glfwSwapBuffers(window);

	return !glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() const
{
	return window;
}