#include "Window.h"
#include <iostream>
#define GLEW_STATIC

int main(int argc, char** argv) {
	Window w(800, 600, "TCC");

	while (!w.shouldClose())
	{
		w.update();
	}
	return 0;
}