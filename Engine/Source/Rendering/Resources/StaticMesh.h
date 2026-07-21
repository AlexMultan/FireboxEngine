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
		void SetMaterial(size_t slotIndex, const Ref<Material>& material, float tiling);

		inline const DynamicArray<Ref<Mesh>>& GetMeshes() const { return m_Meshes; }
		inline const DynamicArray<Ref<Material>>& GetMaterials() const { return m_Materials; }
		inline void SetMaterials(const DynamicArray<Ref<Material>>& materials) { m_Materials = materials; }
		inline const String& GetDirectory() const { return m_Directory; }
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