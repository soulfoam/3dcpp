#pragma once

#include <glm/glm.hpp>
#include "shader.hpp"

class DefaultShader : public Shader
{

public:
	DefaultShader();

	void loadModelMatrix(const glm::mat4 &m);
	void loadViewMatrix(const glm::mat4 &m);
	void loadProjectionMatrix(const glm::mat4 &m);
	void loadLight(const glm::mat4 &m);

private:
	GLuint u_modelMatrix;
	GLuint u_viewMatrix;
	GLuint u_projectionMatrix;
	GLuint u_lightPosition;

	GLuint u_meshColor;
	GLuint u_lightColor;
	GLuint u_fakeLightNormal;
	
};
