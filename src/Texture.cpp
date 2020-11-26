#include "Texture.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const char * path)
	:Texture()
{
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		if(nrChannels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if(nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
		{
			// If this ever happens I can deal with it
			std::cerr << "Error: UNKNOWN: Texture Not RGB or RGBA, Continuing\nFilename: " << path << std::endl;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::initTexture(const float* data, unsigned int nChannels, unsigned int width, unsigned int height)
{
	if (data)
	{
		if (nChannels > 2 && nChannels < 5)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, (nChannels == 3) ? GL_RGB : GL_RGBA, GL_FLOAT, data);
	}
}
void Texture::initTexture(const unsigned char* data, unsigned int nChannels, unsigned int width, unsigned int height)
{
	if (data)
	{
		if (nChannels > 2 && nChannels < 5)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, (nChannels == 3) ? GL_RGB : GL_RGBA, GL_FLOAT, data);
	}
}
