#pragma once

#include <glm/glm.hpp>
#include "drawable.hpp"

class Model
{

public:
	Model(Mesh &mesh, glm::vec3 pos);

	const Drawable &getDrawable()     { return m_drawable; }
	const glm::mat4 &getModelMatrix() { return m_modelMatrix; }
	const glm::vec3 &getPosition()    { return m_position; }
	const glm::vec3 &getRotation()    { return m_rotation; }
	const glm::vec3 &getScale()       { return m_scale; }
	
	void setPosition(const glm::vec3 &v)    { m_position = v; }
	void setRotation(const glm::vec3 &v)    { m_rotation = v; }
	void setScale(const glm::vec3 &v)       { m_scale = v; }
	void setModelMatrix(const glm::mat4 &v) { m_modelMatrix = v; }

private:
	Drawable m_drawable;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_modelMatrix;

};
