/* #ifndef MATERIAL_H_DEFINED
#define MATERIAL_H_DEFINED
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>

struct Material {
	// Shader program
	GLuint m_program1;
	GLuint m_program2;

	// Material parameters
	glm::vec4 m_color;
	GLint m_texture;
	GLint texture_cubemap ;

	//GLuint skyboxVAO, skyboxVBO;

	inline void check() {
		if (m_program1 == 0) {
			throw std::runtime_error("Shader program not initialized");
		}
		if (m_program2 == 0) {
			throw std::runtime_error("Shader program not initialized");
		} 
	}

	Material(): m_program1(0), m_program2(0) {

	}

	virtual ~Material();

	virtual void init();

	virtual void clear();

	void bind();

	virtual void internalBind();

	void setMatrices1(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix);

    void setMatrices2(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix);

	GLint getAttribute1(const std::string& in_attributeName);

	GLint getAttribute2(const std::string& in_attributeName);

	GLint getUniform1(const std::string& in_uniformName);

	GLint getUniform2(const std::string& in_uniformName);
};

#endif
 */

#ifndef MATERIAL_H_DEFINED
#define MATERIAL_H_DEFINED
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>

struct Material
{
	// Shader program
	GLuint m_program;
	GLuint cube_program;

	// Material parameters
	glm::vec4 m_color;
	GLint m_texture, cube;

	inline void check()
	{
		if (m_program == 0)
		{
			throw std::runtime_error("Shader program not initialized");
		}
		if (cube_program == 0)
		{
			throw std::runtime_error("Shader program not initialized");
		}
	}

	Material() : m_program(0), cube_program(0)
	{
	}

	virtual ~Material();

	virtual void init();

	virtual void clear();

	void bind();

	virtual void internalBind();

	void setMatrices(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix);

	void setMatrices_cube(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix);

	GLint getAttribute(const std::string &in_attributeName);

	GLint getUniform(const std::string &in_uniformName);

	GLint getUniform_cube(const std::string &in_uniformName);
};

#endif