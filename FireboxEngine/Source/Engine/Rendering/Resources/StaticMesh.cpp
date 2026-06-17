#include "StaticMesh.h"

namespace Firebox {

	StaticMesh::StaticMesh(const String& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			FIREBOX_CORE_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			return;
		}

		m_Directory = path.substr(0, path.find_last_of('/'));
		ProcessNode(scene->mRootNode, scene);
	}

	void StaticMesh::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
			ProcessNode(node->mChildren[i], scene);
	}

	Ref<Mesh> StaticMesh::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		DynamicArray<Vertex> vertices;
		DynamicArray<uint> indices;
		DynamicArray<Texture> textures;

		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			Vector3 vec;

			vec.x = mesh->mVertices[i].x;
			vec.y = mesh->mVertices[i].y;
			vec.z = mesh->mVertices[i].z;
			vertex.Position = vec;

			if (mesh->HasNormals())
			{
				vec.x = mesh->mNormals[i].x;
				vec.y = mesh->mNormals[i].y;
				vec.z = mesh->mNormals[i].z;
				vertex.Normal = vec;
			}

			if (mesh->mTextureCoords[0])
			{
				Vector2 texVec;

				texVec.x = mesh->mTextureCoords[0][i].x;
				texVec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = texVec;
			}
			else { vertex.TexCoords = Vector2(0.0f, 0.0f); }

			vertices.push_back(vertex);
		}

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		return CreateRef<Mesh>(vertices, indices);
	}
}