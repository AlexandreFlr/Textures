#include "Texture.h"
#include "Vec3.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "stb_image.h"
#include <vector>
#include <iostream>

#include <stdexcept>

GLuint loadTexture2DFromFilePath(const std::string &path)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width = 0 ;
	int height = 0 ;
	int nrChannels = 3;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 3);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << " Failed to load texture " << std::endl;
	}
	stbi_image_free(data);
	setDefaultTexture2DParameters(texture);
	return texture;
}

void setDefaultTexture2DParameters(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
