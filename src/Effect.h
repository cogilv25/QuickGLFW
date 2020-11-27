#pragma once
#include "Shader.h"

#define VERT_SHADER 0x8B31
#define FRAG_SHADER 0x8B30
#define GEO_SHADER 0x8DD9
#define TE_SHADER 0x8E87
#define TC_SHADER 0x8E88

class Effect
{
public:
	unsigned int id;
	unsigned int shaderTypes[5]{ VERT_SHADER, FRAG_SHADER, GEO_SHADER, TE_SHADER, TC_SHADER };
	Shader* shaders[5]{ 0, 0, 0, 0, 0 };

	bool built = false;
public:
	void addShader(Shader& shader);
	void build();
	Effect();
	~Effect();
};

