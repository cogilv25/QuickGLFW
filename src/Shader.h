#pragma once
class Shader
{
public:
	unsigned int id;
	unsigned int shaderType;
	Shader(const char* path, unsigned int type);
	Shader();
};

