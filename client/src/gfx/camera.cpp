#include "camera.hpp"

Camera::Camera(glm::vec3 position)
:
m_fov(60),
m_nearClip(0.1),
m_farClip(2000),
m_aspect(1),
m_viewMatrix(glm::mat4(1))
{
	m_viewMatrix = glm::translate(m_viewMatrix, position);
}

glm::mat4
Camera::getProjectionMatrix()
{
	return glm::perspective(
			glm::radians(m_fov), 
			m_aspect, 
			m_nearClip, 
			m_farClip);
}

glm::mat4
Camera::getViewMatrix()
{
	glm::mat4 view = 
	{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};

	view = glm::transpose(view);
	
	glm::mat4 res = view * m_viewMatrix;

	res[3][0] = -res[3][0];
	res[3][1] = -res[3][1];
	res[3][2] = -res[3][2];

	return res;
}
