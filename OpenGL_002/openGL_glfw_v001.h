#pragma once
#include <vector>
#include <glad/gl.h>
#include <glfw3.h>
#include "constant_V001.h"

class OpenGL_GLFW
{
private:
	
public:
	GLuint VBO, VBOColor, EBO, VAO;
	
	GLuint shaderProgram;

	GLFWwindow* window;
	
	OpenGL_GLFW()
	{}
	~OpenGL_GLFW()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);

		glDeleteProgram(shaderProgram);

		glfwTerminate();
	}
	//Encaps||Abstraction
	void setVBO(GLuint vboParam);
	GLuint* getVBO();

	void setVBOColor(GLuint vboColorParam);
	GLuint* getVBOColor();

	void setEBO(GLuint eboParam);
	GLuint* getEBO();

	void setVAO(GLuint vaoParam);
	GLuint* getVAO();

	void setShaderProgram(GLuint shaderProgramParam);
	GLuint* getShaderProgram();

	GLFWwindow* getWindow();
	void setWindow(GLFWwindow* windowParam);

	//behavior
	int criacaoVBO();

	std::string praLerArquivos(std::string userInput);
	int coresMateriais(std::string vtxShaderFileParam, std::string fgmtShaderFileParam);
	int transformationMatrices(unsigned int index);

	void wireFrame();
	void solidMode();
	void processInput();
	int initWindow();
	int startGlad();
	int renderLoop();
};

class Objeto3D
{
public:

	GLfloat arrayVertex[8][3] = {
			{0.5,0.5,0.5}, //vertice 0
			{-0.5,0.5,0.5},//vertice 1
			{-0.5,-0.5,0.5},//vertice 2
			{0.5,-0.5,0.5}, // vertice 3
			{0.5,-0.5,-0.5}, //vertice 4
			{-0.5,-0.5,-0.5},//vertice 5
			{-0.5,0.5,-0.5},//vertice 6
			{0.5,0.5,-0.5} // vertice 7
	};

	GLfloat arrayCores[8][3] = {
			{0.7,0.0,0.0},//vertice 0
			{0.7,0.0,0.0},//vertice 1
			{0.7,0.0,0.0},//vertice 2
			{0.0,0.5,0.5},//vertice 3
			{0.0,0.5,0.5},//vertice 4
			{0.0,0.5,0.5},//vertice 5
			{0.3,0.0,1.0},//vertice 6
			{0.3,0.0,1.0}//vertice 7
	};

	GLuint arrayIndex[12][3] = {
			{0,1,3},
			{0,1,7},
			{1,2,3},
			{1,6,7},
			{2,5,4},
			{2,5,6},
			{3,2,4},
			{3,4,7},
			{6,1,2},
			{6,5,4},
			{7,0,3},
			{7,6,4}
	};

	Objeto3D()
	{}
	~Objeto3D()
	{}
};
