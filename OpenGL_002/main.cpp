#include "openGL_glfw_v001.h"
#include "constant_V001.h"

int main()
{
	OpenGL_GLFW graphics;

	std::string vertexShaderFile = graphics.praLerArquivos(VERTEX_SHADER_FILE);
	std::string fragShaderFile = graphics.praLerArquivos(FRAGMENT_SHADER_FILE);

	graphics.initWindow();

	graphics.coresMateriais(vertexShaderFile, fragShaderFile);
	
	graphics.criacaoVBO();

	graphics.renderLoop();

	return 0;
}