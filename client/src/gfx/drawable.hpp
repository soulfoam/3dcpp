#pragma once

#include <GL/glew.h>
#include "meshBundle.hpp"

class Drawable
{
public:	
	
	Drawable(Mesh &mesh);
	~Drawable();
	
	GLuint   getVao()         const { return m_vao; }
	uint32_t getVertexCount() const { return m_vertexCount; }
	uint32_t getIndiceCount() const { return m_indiceCount; }
	bool     getVisible()     const { return m_visible; }

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	uint32_t m_vertexCount;
	uint32_t m_indiceCount;
	bool m_visible;
};
