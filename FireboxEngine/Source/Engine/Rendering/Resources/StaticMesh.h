#pragma once

#include "Mesh.h"
#include "Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Firebox {

	struct LoadedTextures 
	{ 
		DynamicArray<String> Paths; 
		DynamicArray<Ref<Texture>> Textures; 
	};

	class FIREBOX_API StaticMesh
	{
	public:
		StaticMesh(const String& path);

		void SetMaterial(size_t slotIndex, const Ref<Material>& material);

		const DynamicArray<Ref<Mesh>>& GetMeshes() const { return m_Meshes; }
		const DynamicArray<Ref<Material>>& GetMaterials() const { return m_Materials; }
	private:
		void LoadModel(const String& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
		Ref<Material> ProcessMaterial(aiMaterial* mat);
		Ref<Texture> LoadMaterialTexture(const String& path);

		DynamicArray<Ref<Mesh>> m_Meshes;
		DynamicArray<Ref<Material>> m_Materials;
		String m_Directory;
		LoadedTextures m_LoadedTextures;
	};
}