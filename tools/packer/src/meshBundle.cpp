#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>     
#include <core/ext/io.hpp>
#include "meshBundle.hpp"

static const uint32_t VERSION = 1;

static void processAiMesh(aiMesh *am, std::vector<Vertex> &verts, std::vector<uint32_t> &indices)
{
	Vertex v;

	for (uint32_t i = 0; i < am->mNumVertices; i++)
	{
		v.pos.x = am->mVertices[i].x;
		v.pos.y = am->mVertices[i].y;
		v.pos.z = am->mVertices[i].z;

		if (am->mTextureCoords[0])
		{
			v.uv.x = am->mTextureCoords[0][i].x;
			v.uv.y = am->mTextureCoords[0][i].y;
		}
		else
		{
			v.uv[0] = 0.0f;
			v.uv[1] = 0.0f;
		}

		v.norm.x = am->mNormals[i].x;
		v.norm.y = am->mNormals[i].y;
		v.norm.z = am->mNormals[i].z;

		verts.push_back(v);
	}

	for (uint32_t i = 0; i < am->mNumFaces; i++)
	{
		aiFace f = am->mFaces[i];

		for (uint32_t j = 0; j < f.mNumIndices; j++) indices.push_back(f.mIndices[j]);
	}
	
}

MeshBundle::MeshBundle(const std::string &filePath)
{

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);

	if (!scene)
	{
		std::cout << importer.GetErrorString() << std::endl;
		return;
	}

	for (uint32_t i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh *am = scene->mMeshes[i];
		std::vector<Vertex> verts;
		std::vector<uint32_t> indices;

		processAiMesh(am, verts, indices);
		
		std::string name = am->mName.C_Str();
		if (filePath.find(".obj") != std::string::npos)
		{
			auto pos = name.find_last_of("_");
			if (pos != std::string::npos) name.erase(pos);
		}
		
		m_meshes.emplace_back(name, std::move(verts), std::move(indices));
	}
}

void MeshBundle::saveToFile(const std::string &outputName)
{
		
	BinaryWriter w;
	w.writeU32(VERSION);
	w.writeU32(m_meshes.size());

	for (uint32_t i = 0; i < m_meshes.size(); i++)
	{
		auto m = m_meshes[i];
		w.writeString(m.getName());	

		auto verts = m.getVertices();
		w.writeU32(verts.size());
		for (uint32_t i = 0; i < verts.size(); i++)
		{
			w.writeVec3(verts[i].pos);
			w.writeVec2(verts[i].uv);
			w.writeVec3(verts[i].norm);
		}

		auto indices = m.getIndices();
		w.writeU32(indices.size());
		for (uint32_t i = 0; i < indices.size(); i++)
		{
			w.writeU32(indices[i]);
		}

	}
	
	w.saveToFile(outputName);

	print();
}

void MeshBundle::print()
{
	for (auto &mesh: m_meshes)
	{
		mesh.print();
	}
}
