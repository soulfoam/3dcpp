#include "masterRenderer.hpp"

MasterRenderer::MasterRenderer()
:
m_display(Display("MORPG", glm::vec2(1280, 720))),
m_camera(Camera(glm::vec3(0, -12, 1)))
{
	m_camera.setAspect(m_display.getWindowAspect());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void
MasterRenderer::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
	
	m_modelRenderer.render(m_camera);

	SDL_GL_SwapWindow(m_display.getWindow());
}

