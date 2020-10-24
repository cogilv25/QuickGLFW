#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(const char* vfile,const char * ffile)
{
	std::ifstream vertFile;
	std::ifstream fragFile;

	std::stringstream stream;
	std::string str;
	const char* source;

	unsigned int vertID, fragID;
	int success;
	char log[512];
	vertID = glCreateShader(GL_VERTEX_SHADER);
	fragID = glCreateShader(GL_FRAGMENT_SHADER);

	vertFile.open(vfile);
	fragFile.open(ffile);

	stream << vertFile.rdbuf();
	str = stream.str();
	source = str.c_str();


	glShaderSource(vertID, 1, &source, 0);
	glCompileShader(vertID);
	
	glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertID, 512, NULL, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
	};

	vertFile.close();

	//clear stream
	stream.str(std::string());
	stream << fragFile.rdbuf();
	str = stream.str();
	source = str.c_str();

	glShaderSource(fragID, 1, &source, 0);
	glCompileShader(fragID);

	glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragID, 512, NULL, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
	};

	fragFile.close();

	id = glCreateProgram();
	glAttachShader(id, vertID);
	glAttachShader(id, fragID);
	glLinkProgram(id);
	// print linking errors if any
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertID);
	glDeleteShader(fragID);
}