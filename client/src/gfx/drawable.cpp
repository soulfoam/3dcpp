#include "drawable.hpp"

Drawable::Drawable(Mesh &mesh) 
:
m_vertexCount(mesh.getVertices().size()),
m_indiceCount(mesh.getIndices().size()),
m_visible(true)
{

	glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
    //glGenBuffers(1, &mesh->instance.pos_buffer);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
			GL_ARRAY_BUFFER, 
			mesh.getVertices().size() * sizeof(Vertex),
			&mesh.getVertices()[0],
			GL_STATIC_DRAW);

	uint32_t slot = 0;
	glVertexAttribPointer(slot++, 3, GL_FLOAT, GL_FALSE, 
			sizeof(Vertex), (void*)0);
	glVertexAttribPointer(slot++, 2, GL_FLOAT, GL_FALSE, 
			sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(slot++, 3, GL_FLOAT, GL_FALSE, 
			sizeof(Vertex), (void*)(5 * sizeof(float)));		

	for (uint32_t i = 0; i < slot; i++) glEnableVertexAttribArray(i);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, 
			mesh.getIndices().size() * sizeof(uint32_t), 
			&mesh.getIndices()[0], 
			GL_STATIC_DRAW);

	glBindVertexArray(0);

}

Drawable::~Drawable()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

