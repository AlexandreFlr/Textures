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
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 1);
	unsigned char* normalMap = new unsigned char[width * height * 3] ;
        if(data){
            float s = 1 ;
            for(int j = 1 ; j < height-1 ; j++){
                for(int i = 1 ; i < width-1 ; i++){
                    float du = (s/2) * ((int)data[j*width + i + 1] - (int)data[j*width + i - 1]);
                    float dv = (s/2) * ((int)data[(j+1)*width + i] - (int)data[(j-1)*width + i]);
                    Vec3 diru = Vec3(1,0,du) ;
                    Vec3 dirv = Vec3(0,1,dv) ;
                    Vec3 m = Vec3::cross(diru,dirv) ;
                    m.normalize() ;
                    normalMap[j*width*3 + i*3] = std::floor((m[0] * 0.5 + 0.5)*255) ;
                    normalMap[j*width*3 + i*3 + 1] = std::floor((m[1] * 0.5 + 0.5)*255) ;
                    normalMap[j*width*3 + i*3 + 2] = std::floor((m[2] * 0.5 + 0.5)*255) ;
                }
            }
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, normalMap);
		glGenerateMipmap(GL_TEXTURE_2D);
		delete[] normalMap ;
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
