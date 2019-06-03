#include <core/ext/io.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "meshBundle.hpp"

const uint32_t VERSION = 1;

MeshBundle::MeshBundle(const std::string &filePath)
{
	BinaryReader r(filePath);
	uint32_t ver = r.readU32();

	if (ver != VERSION)
	{
		std::cout << "Version mismatch MeshBundle GET PROPER LOGGING STD::COUT IS SHIT" << std::endl;
	}

	uint32_t meshCount = r.readU32();

	for (uint32_t i = 0; i < meshCount; i++)
	{
		std::string name = r.readString();

		uint32_t vertCount = r.readU32();
		std::vector<Vertex> verts;
		verts.reserve(vertCount);
		for (uint32_t i = 0; i < vertCount; i++)
		{
			glm::vec3 pos = r.readVec3();
			glm::vec2 uv = r.readVec2();
			glm::vec3 norm = r.readVec3();

			verts.emplace_back(pos, uv, norm);
		}

		uint32_t indiceCount = r.readU32();
		std::vector<uint32_t> indices;
		indices.reserve(indiceCount);
		for (uint32_t i = 0; i < indiceCount; i++)
		{
			uint32_t indice = r.readU32();
			indices.push_back(indice);
		}
		
		m_meshes.emplace_back(name, std::move(verts), std::move(indices));
	}
}

Mesh&
MeshBundle::getMesh(const std::string &name)
{
	for (uint32_t i = 0; i < m_meshes.size(); i++)
	{
		auto &m = m_meshes[i];
		if (m.getName() == name) return m;
	}
	
	std::cout << "WARNING: Mesh " << name << " was not found in bundle!";

	return m_meshes[0];
}

