#pragma once
#include <GLFW/glfw3.h>
#include <GL/glew.h>

class Window
{
public:
	Window(int width = 800, int height = 600, const char* title = "");
	void update();
	~Window();
};

