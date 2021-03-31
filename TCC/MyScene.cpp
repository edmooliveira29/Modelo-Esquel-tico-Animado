#include "MyScene.h"
#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include "Util.h"

GLint checkProgramLink(GLuint program) {
	GLint success = 0;
	GLchar infoLog[512];
	glGetShaderiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}

	return success;
}

GLint checkShaderCompilation(GLuint shader) {
	GLint success = 0;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}

	return success;
}



MyScene::MyScene() {
	std::stringstream vertexSourceStream;
	std::stringstream fragmentSourceStream;
	
	//Carregando os shaders que são os vertex e 
	loadFile("vertex.vs", vertexSourceStream);
	loadFile("fragment.fs", fragmentSourceStream);

	//Carregando o conteúdo inteiro dos arquivos 
	std::string vertexSource = vertexSourceStream.str();
	std::string fragmentSource = fragmentSourceStream.str();

	const char* buff;

	//Criando um programa para associar com os shaders
	m_ShaderProgram = glCreateProgram();

	//Preparando os shaders para associoar aos programas. 
		// Vertex Shader
	buff = vertexSource.c_str();
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Parametros do glShaderSource
			/*
				1. Identificado 
				2. Numero de strings
				3. array com todas as strings
				4. NULL -> Uma string quando termina tem tamanho zero então o sistema entende que acabou. 
			*/
	glShaderSource(m_vertexShader, 1, &buff, NULL);
		//Compilando e checando se a compilação deu certo
	glCompileShader(m_vertexShader);
	checkShaderCompilation(m_vertexShader);

		//Associando o shader ao programa e marcando o shader para ser excluido. 
	glAttachShader(m_ShaderProgram, m_vertexShader);
	glDeleteShader(m_vertexShader);

		// Fragment Shader (Igual ao shader do vertex)
	buff = fragmentSource.c_str();
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &buff, NULL);
	glCompileShader(m_FragmentShader);
	checkShaderCompilation(m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glDeleteShader(m_FragmentShader);

	//Link shader program e checando se houve algum erro na linkagem 
	glLinkProgram(m_ShaderProgram);
	checkProgramLink(m_ShaderProgram);

	//Desenhando o triangulo
	m_Vertices = new GLfloat[18]{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	//Criando identificaddores para o array de buffer
	glGenBuffers(1, &m_VBO);
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	//Criando os vertices e atributos
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GL_FLOAT), m_Vertices, GL_STATIC_DRAW);

	//Especificando como os dados do triangulo serão interpretados 
		//Vertices
	glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT)*6,(GLvoid*)0);
		//Cores
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (GLvoid*)(3* sizeof(GL_FLOAT)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

}


MyScene::~MyScene() {
	glDeleteProgram(m_ShaderProgram);
}


void MyScene::update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Renderizando a imagem
	glUseProgram(m_ShaderProgram);

	//Informando em qual buffer esta os dados
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}