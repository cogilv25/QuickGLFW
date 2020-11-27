#include "Effect.h"
#include <iostream>
#include <glad/glad.h>

void Effect::addShader(Shader& shader)
{
	if (!built)
	{
		if (shader.id > 0)
		{
			for (int i = 0; i < 5; i++)
			{
				if (shaderTypes[i] == shader.shaderType)
				{
					shaders[i] = &shader;
					return;
				}
			}
		}
		else
		{
			std::cerr << "Attempted to add invalid shader to effect\n";
		}
	}
	else
	{
		std::cerr << "Attempted to add a shader to an effect that is already linked\n";
	}
	std::cerr << "Attempted to add a shader of an invalid type to an effect\n";
}

void Effect::build()
{
	for (int i = 0; i < 5; i++)
	{
		if (shaders[i] != 0)
		{
			glAttachShader(id, shaders[i]->id);
		}
	}
	glLinkProgram(id);

	//Error Check
	int success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char log[512];
		glGetProgramInfoLog(id, 512, NULL, log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
	}

	built = true;
}

Effect::Effect()
{
	id = glCreateProgram();
}

Effect::~Effect()
{
	glDeleteProgram(id);
}
