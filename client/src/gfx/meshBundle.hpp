#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <core/ext/rof.hpp>

struct Vertex
{
	Vertex(glm::vec3 p, glm::vec2 u, glm::vec3 n)
	:
	pos(p),
	uv(u),
	norm(n)
	{}

	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 norm;
};

class Mesh
{

public:
	Mesh(const std::string &name, std::vector<Vertex> &&vertices, std::vector<uint32_t> &&indices)
	:
	m_name(name),
	m_vertices(std::move(vertices)),
	m_indices(std::move(indices))
	{

	}
	
	const std::string &getName() { return m_name; }
	const std::vector<Vertex> &getVertices() { return m_vertices; }
	const std::vector<uint32_t> &getIndices() { return m_indices; }

	void print()
	{
		std::cout 
		<< m_name 
		<< " (Verts: " << m_vertices.size() 
		<< ")(Indices: " << m_indices.size() << ")" 
		<<	std::endl;
	}

	Mesh (const Mesh &) = delete;
	Mesh &operator=(const Mesh &) = delete;
	Mesh (Mesh &&other) 
	:
	m_name(std::move(other.m_name)),
	m_vertices(std::move(other.m_vertices)),
	m_indices(std::move(other.m_indices))
	{

	}
	
private:
	std::string m_name;
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;	
	
};

class MeshBundle
{

public:
	MeshBundle(const std::string &filePath);

	Mesh &getMesh(const std::string &name);

private:
	std::vector<Mesh> m_meshes;
};


