#pragma once


class Texture
{
public:
	unsigned int id;
	Texture();
	Texture(const char* filename);
	~Texture();
};