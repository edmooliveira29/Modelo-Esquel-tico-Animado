#include "Window.h"
#include <iostream>
Window::Window(int width, int height, const char* title) {
	// Inicializa a biblioteca GLFW
	if (glfwInit()) {
		std::cerr << "Erro inicializando GLFW" << std::endl;
		return;
	}
	// Solicitando que seja criado um contexto openGl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);

}

void Window::update() {

}

Window::~Window() {

}