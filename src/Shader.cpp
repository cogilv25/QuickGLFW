#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader()
{
	id = 0;
}

Shader::Shader(const char* path, unsigned int type)
{
	std::ifstream file;

	std::stringstream stream;
	std::string str;

	id = glCreateShader(type);
	shaderType = type;

	file.open(path);

	stream << file.rdbuf();
	str = stream.str();

	file.close();

	const char* source;
	source = str.c_str();

	glShaderSource(id, 1, &source, 0);
	glCompileShader(id);

	//Error Check
	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char log[512];
		glGetShaderInfoLog(id, 512, NULL, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
	};
}