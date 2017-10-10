#pragma once

#include <GL/glew.h>
#include <glfw3.h>

#include "Log.h"

class Window
{
private:

	GLFWwindow *window;

public:

	Window(int w, int h, const char *title);

	bool open();

	GLFWwindow* getWindow() const;
};