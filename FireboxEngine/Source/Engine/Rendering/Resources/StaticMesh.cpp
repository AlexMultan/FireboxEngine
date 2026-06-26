#include "StaticMesh.h"
#include "Engine/Rendering/Renderer3D.h"

namespace Firebox {

	StaticMesh::StaticMesh(const String& path)
	{
		LoadModel(path);
	}

	void StaticMesh::SetMaterial(size_t slotIndex, const Ref<Material>& material)
	{
		if (slotIndex < m_Materials.size())
			m_Materials[slotIndex] = material;
	}

	void StaticMesh::LoadModel(const String& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | 
			aiProcess_CalcTangentSpace | aiProcess_GenUVCoords | aiProcess_TransformUVCoords);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			FB_CORE_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
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

			Ref<Material> material;
			if (mesh->mMaterialIndex > 0)
			{
				aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
				material = ProcessMaterial(aiMat);
			}
			else if(mesh->mMaterialIndex < 1)
			{
				material = Renderer3D::GetDefaultMaterial();
			}
			m_Materials.push_back(material);
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
			ProcessNode(node->mChildren[i], scene);
	}

	Ref<Mesh> StaticMesh::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		DynamicArray<Vertex> vertices;
		DynamicArray<uint> indices;

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
			else
			{
				Vector2 fallbackCoords;
				fallbackCoords.x = mesh->mVertices[i].x;
				fallbackCoords.y = mesh->mVertices[i].y;
				fallbackCoords.x *= 5.0f;
				fallbackCoords.y *= 5.0f;

				vertex.TexCoords = fallbackCoords;
			}

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

	Ref<Material> StaticMesh::ProcessMaterial(aiMaterial* mat)
	{
		auto material = CreateRef<Material>();

		if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString path;
			mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
			material->SetDiffuseTexture(LoadMaterialTexture(m_Directory + "/" + path.C_Str()));
		}

		if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString path;
			mat->GetTexture(aiTextureType_SPECULAR, 0, &path);
			material->SetSpecularTexture(LoadMaterialTexture(m_Directory + "/" + path.C_Str()));
		}

		float shininess = 32.0f;
		mat->Get(AI_MATKEY_SHININESS, shininess);
		material->SetShininess(shininess);

		return material;
	}

	Ref<Texture> StaticMesh::LoadMaterialTexture(const String& path)
	{
		for (size_t i = 0; i < m_LoadedTextures.Paths.size(); i++)
		{
			if (m_LoadedTextures.Paths[i] == path)
				return m_LoadedTextures.Textures[i];
		}

		auto texture = Texture::Create(path);
		m_LoadedTextures.Paths.push_back(path);
		m_LoadedTextures.Textures.push_back(texture);
		return texture;
	}
}