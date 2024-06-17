#include <string>
#include <fstream>

#include "openGL_glfw_v001.h"
#include "constant_V001.h"

#include <glfw3.h>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

//encaps
void OpenGL_GLFW::setVBO(GLuint vboParam)
{
	this->VBO = vboParam;
}

GLuint* OpenGL_GLFW::getVBO()
{
	return &VBO;
}

void OpenGL_GLFW::setVBOColor(GLuint vboColorParam)
{
	this->VBOColor = vboColorParam;
}

GLuint* OpenGL_GLFW::getVBOColor()
{
	return &VBOColor;
}

void OpenGL_GLFW::setEBO(GLuint eboParam)
{
	this->EBO = eboParam;
}

GLuint* OpenGL_GLFW::getEBO()
{
	return &EBO;
}

void OpenGL_GLFW::setVAO(GLuint vaoParam)
{
	this->VAO = vaoParam;
}

GLuint* OpenGL_GLFW::getVAO()
{
	return &VAO;
}

void OpenGL_GLFW::setShaderProgram(GLuint shaderProgramParam)
{
	this->shaderProgram = shaderProgramParam;
}

GLuint* OpenGL_GLFW::getShaderProgram()
{
	return &shaderProgram;
}

GLFWwindow* OpenGL_GLFW::getWindow()
{
	return window;
}

void OpenGL_GLFW::setWindow(GLFWwindow* windowParam)
{
	this->window = windowParam;
}

//behavior

void resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void OpenGL_GLFW::wireFrame() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OpenGL_GLFW::solidMode() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGL_GLFW::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		wireFrame();
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		solidMode();
	}
}

int OpenGL_GLFW::initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* windowLocal = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GLFW_WINDOW_NAME.c_str(), NULL, NULL);

	if (windowLocal == NULL) 
	{ 
		glfwTerminate(); 
		return -1; 
	}
	else
	{
		setWindow(windowLocal);
	}

	glfwMakeContextCurrent(windowLocal);
	glfwSetFramebufferSizeCallback(windowLocal, resize);

	startGlad();

	glEnable(GL_DEPTH_TEST);

	return 0;
}

int OpenGL_GLFW::startGlad()
{
	int version = gladLoadGL(glfwGetProcAddress);
	if (version == 0)
	{
		return -1;
	}
	return 0;
}

int OpenGL_GLFW::renderLoop()
{

	while (!glfwWindowShouldClose(window))
	{
		processInput();

		glClearColor(BACKGROUND_COLOR_RED, BACKGROUND_COLOR_GREEN, BACKGROUND_COLOR_BLUE, BACKGROUND_COLOR_ALPHA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);

		for (unsigned int i = 0; i <= 9; i++) {

			transformationMatrices(i);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

std::string OpenGL_GLFW::praLerArquivos(std::string userInput)
{
	std::fstream arquivoLido(userInput, std::fstream::in);
	std::string arquivoSaida;
	std::string* novaLinha = new std::string;

	if (arquivoLido.is_open())
	{
		while (arquivoLido)
		{
			std::getline(arquivoLido, *novaLinha);
			arquivoSaida = arquivoSaida + *novaLinha + "\n";
		}
	}

	delete(novaLinha);
	arquivoLido.close();

	return arquivoSaida;
}

int OpenGL_GLFW::coresMateriais(std::string vtxShaderFileParam, std::string fgmtShaderFileParam)
{
	int compilado;
	char logErro[512];

	//vertex shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* vertexShaderSource = vtxShaderFileParam.c_str();

	//compila o shader	
	glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShaderID);

	//verifies if shader compilation got succesful
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &compilado);

	if (!compilado)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, logErro);
		return -1;
	}

	//fragment shader
	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);//cria um objeto do tipo frag shader
	std::string outroArquivo;
	const GLchar* fragShaderSource = fgmtShaderFileParam.c_str();

	//Shader compilation
	glShaderSource(fragShaderID, 1, &fragShaderSource, NULL);
	glCompileShader(fragShaderID);

	//verifies shader compilation got succesful
	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &compilado);

	if (!compilado)
	{
		return -1;
	}

	//creates shader program object
	shaderProgram = glCreateProgram();
	setShaderProgram(shaderProgram);

	//bind shader program and the shader itself
	glAttachShader(shaderProgram, vertexShaderID);
	glAttachShader(shaderProgram, fragShaderID);

	//bind tudo
	glLinkProgram(shaderProgram);

	//went succesful
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compilado);

	if (!compilado)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, logErro);
		return -1;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragShaderID);

	compilado;

	return 0;
}

int OpenGL_GLFW::transformationMatrices(unsigned int index) {

	//send the transformation matrix data to shader
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	glBindVertexArray(VAO);

	modelMatrix = glm::rotate(modelMatrix, 
							 ((float)glfwGetTime() * glm::radians(2.0f)) * 20.0f, 
							 glm::vec3(0.0f, 1.0f, 0.0f));

	viewMatrix = glm::translate(viewMatrix, 
								glm::vec3(0.0f, 
								0.0f, 
								glm::sin(glfwGetTime()) 
								* glm::radians(-200.0f)));

	projectionMatrix = glm::perspective(glm::radians(45.0f), 
										(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 
										0.1f, 
										100.0f);

	int model = glGetUniformLocation(shaderProgram, "modelMatrix");
	int view = glGetUniformLocation(shaderProgram, "viewMatrix");
	int projection = glGetUniformLocation(shaderProgram, "projectionMatrix");

	glUniformMatrix4fv(model, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(view, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projection, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, 0);

	return 0;
}

int OpenGL_GLFW::criacaoVBO()
{

	Objeto3D primitive3D;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO); 

	glBindVertexArray(VAO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(primitive3D.arrayVertex), &primitive3D.arrayVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//colors
	glGenBuffers(1, &VBOColor);
	glBindBuffer(GL_ARRAY_BUFFER, VBOColor);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(primitive3D.arrayCores), &primitive3D.arrayCores, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO);
	
	//EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(primitive3D.arrayIndex), &primitive3D.arrayIndex, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 1);

	glBindVertexArray(0);

	return 0;
}