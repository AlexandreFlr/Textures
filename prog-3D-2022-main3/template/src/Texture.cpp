/*#include "Texture.h"
#include "Vec3.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "stb_image.h"
#include <vector>
#include <iostream>

#include <stdexcept>

GLuint loadTexture2DFromFilePath(const std::string& path) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width = 0;
	int height = 0;
	int channels = 3;
	unsigned char *data = stbi_load(path.c_str() , &width , &height , &channels , 3);
    unsigned char* normalMap = new unsigned char[width * height * 3] ;
    if(data){
        float s = 1 ;
        for(int j = 1 ; j < height-1 ; j++){
            for(int i = 1 ; i < width-1 ; i++){
                //std::cout<<"donnee = "<<(int)data[i*width + j]<<" "<<std::endl ;
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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	    glGenerateMipmap(GL_TEXTURE_2D);
        delete[] normalMap ;
	}
	else
        {
            std ::cout << " Failed to load texture " << std ::endl;
        }  
	
	stbi_image_free(data);
	setDefaultTexture2DParameters(texture);
	return texture;
}

unsigned int loadCubemap ( std::vector<std::string> facesPath ) {
    unsigned int textureID ;
    glGenTextures (1 , & textureID ) ;
    glBindTexture ( GL_TEXTURE_CUBE_MAP , textureID ) ;
    int width , height , nrChannels ;
    for ( unsigned int i = 0; i < facesPath.size () ; i ++) {
        unsigned char * data = stbi_load ( facesPath[i].c_str() , & width , & height , & nrChannels , 0) ;
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << facesPath[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri ( GL_TEXTURE_CUBE_MAP , GL_TEXTURE_MIN_FILTER , GL_LINEAR ) ;
    glTexParameteri ( GL_TEXTURE_CUBE_MAP , GL_TEXTURE_MAG_FILTER , GL_LINEAR ) ;
    glTexParameteri ( GL_TEXTURE_CUBE_MAP , GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE ) ;
    glTexParameteri ( GL_TEXTURE_CUBE_MAP , GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE ) ;
    glTexParameteri ( GL_TEXTURE_CUBE_MAP , GL_TEXTURE_WRAP_R , GL_CLAMP_TO_EDGE ) ;
    return textureID ;
}

void setDefaultTexture2DParameters(GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
*/

/* #include "Texture.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include "stb_image.h"
#include "math.h"
#include <stdexcept>
#include "Vec3.h"
#include <vector>
#include "iostream"
GLuint loadTexture2DFromFilePath(const char *path)
{
	GLuint texture;
	glGenTextures(1, &texture);
	// glBindTexture(GL_TEXTURE_2D, texture);

	int width = 0;
	int height = 0;
	int channels = 3;
	unsigned char *data = stbi_load(path, &width, &height, &channels, 3);
	unsigned char *NormalMap = new unsigned char[width * height * 3];
	int s = 2;
	if (data)
	{
		/* for (int i = 1; i < width - 1; i++)
		{
			for (int j = 1; j < height - 1; j++)
			{
				float dx = (s / 2) * ((int)data[(i - 1) * width + j] - (int)data[(i - 1) * width + j]);
				float dy = (s / 2) * ((int)data[i * width + (j + 1)] - (int)data[i * width + (j - 1)]);
				Vec3 dirU = Vec3(1, 0, dx);
				Vec3 dirV = Vec3(0, 1, dy);
				Vec3 m = (Vec3::cross(dirU, dirV));
				m.normalize();

				NormalMap[i * width * 3 + j * 3] = std::floor((m[0] * 0.5 + 0.5) * 255);
				NormalMap[i * width * 3 + (j * 3) + 1] = std::floor((m[1] * 0.5 + 0.5) * 255);
				NormalMap[i * width * 3 + (j * 3) + 2] = std::floor((m[2] * 0.5 + 0.5) * 255);
			}
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NormalMap);
		glGenerateMipmap(GL_TEXTURE_2D);

		delete[] NormalMap; 
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std ::cout << " Failed to load texture " << std ::endl;
		stbi_image_free(data);
	}
	setDefaultTexture2DParameters(texture);
	return texture;
}

GLuint loadCubemap(std::vector<std::string> cube_faces)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < cube_faces.size(); i++)
	{
		unsigned char *data = stbi_load(cube_faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "failed to load: " << cube_faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture;
}

void setDefaultTexture2DParameters(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
} */

#include "Texture.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include "stb_image.h"
#include "math.h"
#include <stdexcept>
#include "Vec3.h"
#include <vector>
#include "iostream"

GLuint loadTexture2DFromFilePath(const std::string& path) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	setDefaultTexture2DParameters(texture);
	int width = 0;
	int height = 0;
	int channels = 3;
	unsigned char *data = stbi_load(path.c_str() , &width , &height , &channels , 1);
    unsigned char* normalMap = new unsigned char[width * height * 3] ;
    if(data){
        /* float s = 1 ;
        for(int j = 1 ; j < height-1 ; j++){
            for(int i = 1 ; i < width-1 ; i++){
                //std::cout<<"donnee = "<<(int)data[i*width + j]<<" "<<std::endl ;
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
        }  */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	    glGenerateMipmap(GL_TEXTURE_2D);
        delete[] normalMap ;
	}
	else
        {
            std ::cout << " Failed to load texture " << std ::endl;
        }  
	
	stbi_image_free(data);
	//setDefaultTexture2DParameters(texture);
	return texture;
}

GLuint loadCubeMap(std::vector<std::string> cube_faces)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	int width, height, nrChannels;
	for (unsigned int i = 0; i < cube_faces.size(); i++)
	{
		unsigned char *data = stbi_load(cube_faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "failed to load: " << cube_faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

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