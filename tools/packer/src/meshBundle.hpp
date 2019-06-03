#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>     

struct Vertex
{
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
	{}
	
	const std::string &getName() {return m_name;}
	const std::vector<Vertex> &getVertices() {return m_vertices;}
	const std::vector<uint32_t> &getIndices() {return m_indices;}

	void print()
	{
	std::cout << 
		m_name << 
		" (Verts: " << m_vertices.size() 
		<< ")(Indices: " << m_indices.size() << ")" <<
		std::endl;
	}

	Mesh &operator=(const Mesh &) = delete;
	
private:
	std::string m_name;
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;	
	
};

class MeshBundle
{

public:
	MeshBundle(const std::string &filePath);

	void saveToFile(const std::string &outputName);
	void print();
	
private:
	std::vector<Mesh> m_meshes;		

};
