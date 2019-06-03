#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position);

	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	void setAspect(float aspect) { m_aspect = aspect; }

private:
	float m_fov;
	float m_nearClip;
	float m_farClip;
	float m_aspect;
	glm::mat4 m_viewMatrix;
};
