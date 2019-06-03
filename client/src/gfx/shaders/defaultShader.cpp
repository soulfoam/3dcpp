#include <iostream>
#include "defaultShader.hpp"

DefaultShader::DefaultShader()
:
Shader("defaultVert.glsl", "defaultFrag.glsl")
{
	compile();

	u_modelMatrix      = getUniformLocation("u_model");
	u_viewMatrix       = getUniformLocation("u_view");
	u_projectionMatrix = getUniformLocation("u_projection");
	u_meshColor        = getUniformLocation("u_meshColor");

	//std::cout << " " << u_modelMatrix << " " << u_viewMatrix << std::endl;
}

void
DefaultShader::loadModelMatrix(const glm::mat4 &m)
{
	loadMat4(u_modelMatrix, m);	
}

void
DefaultShader::loadViewMatrix(const glm::mat4 &m)
{
	loadMat4(u_viewMatrix, m);	
}

void
DefaultShader::loadProjectionMatrix(const glm::mat4 &m)
{
	loadMat4(u_projectionMatrix, m);	
}

