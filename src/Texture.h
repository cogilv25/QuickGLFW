#pragma once


class Texture
{
public:
	unsigned int id;
	Texture();
	Texture(const char* path);
	~Texture();
	void initTexture(const float* data, unsigned int nChannel, unsigned int width, unsigned int height);
	void initTexture(const unsigned char* data, unsigned int nChannels, unsigned int width, unsigned int height);
};