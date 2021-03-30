#include "Window.h"
#include <iostream>
#include "Scene.h"

Window::Window(int width, int height, const char* title) {
	m_ShouldClose = true;

	// Inicializa a biblioteca GLFW
	if (!glfwInit()) {
		std::cerr << "Erro inicializando GLFW" << std::endl;
		return;
	}
	// Definindo os atributos do contexto OpenGL
	// Solicitando que seja criado um contexto openGl 3.2
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);

	// Executando todas as funcões do opengl e informando se algo deu errado no openGl
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_FALSE);

	glfwSetErrorCallback(Window::errorCallback);

		//Criando a Janela
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

		if (!m_Window) {
			std::cerr << "Erro ao criar Janela" << std::endl;
			return;
		}

		//Transformar o contexto atual
		glfwMakeContextCurrent(m_Window);

		GLenum glewInitErr = glewInit();

		if (glewInitErr != GLEW_OK) {
			std::cerr << "Erro ao iniciar o GLEW" << glewGetErrorString(glewInitErr) << std::endl;
			return;
		}

		//Mostrando dado do ambiente
		const GLubyte* renderer = glGetString(GL_RENDERER);
		const GLubyte* version = glGetString(GL_VERSION);
		std::cerr << "Renderizador: " << renderer << std::endl;
		std::cerr << "Versão openGL suportada :" << version << std::endl;
		
		//Limpar o bufffer de cor para limpar a tela e colocando uma cor específica
		glClearColor(1.0f, 1.0f, 1.0f, 0);

		m_ShouldClose = false;
}

void Window::update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Atualizando os eventos da janela
	glfwPollEvents();

	if (m_scene) {
		m_scene->update();
	}

	//Pintar na janela uma cor
	glfwSwapBuffers(m_Window);

	//Fechando a janela
	if (!m_ShouldClose) {
		m_ShouldClose = (glfwWindowShouldClose(m_Window) == GL_TRUE);
	}
}

Window::~Window() {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::errorCallback(int error, const char* description) {
	std::cerr << "Error :" << error << ": "<< description << std::endl;

}