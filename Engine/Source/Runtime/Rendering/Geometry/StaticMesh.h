#pragma once

#include "Mesh.h"
#include "Rendering/Materials/Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Firebox {

	struct LoadedTextures 
	{ 
		std::vector<String> Paths; 
		std::vector<Ref<Texture>> Textures; 
	};

	struct BoneInfo
	{
		int Id;
		Mat4 Offset;
	};

	class FIREBOX_API StaticMesh
	{
	public:
		StaticMesh(const String& path);

		void SetMaterial(size_t slotIndex, const Ref<Material>& material);
		void SetMaterial(size_t slotIndex, const Ref<Material>& material, float tiling);

		inline const std::vector<Ref<Mesh>>& GetMeshes() const { return m_Meshes; }
		inline const std::vector<Ref<Material>>& GetMaterials() const { return m_Materials; }
		inline void SetMaterials(const std::vector<Ref<Material>>& materials) { m_Materials = materials; }
		inline const String& GetDirectory() const { return m_Directory; }
		inline const String& GetRelativePath() const { return m_RelativePath; }
		inline auto& GetBoneInfoMap() { return m_BoneInfoMap; }
		inline int& GetBoneCount() { return m_BoneCounter; }

	private:
		void LoadModel(const String& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
		Ref<Material> ProcessMaterial(aiMaterial* mat);
		Ref<Texture> LoadMaterialTexture(const String& path);
		void SetVertexBoneDataDefault(Vertex& vertex);
		void SetVertexBoneData(Vertex& vertex, int boneId, float weight);
		void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);

		std::vector<Ref<Mesh>> m_Meshes;
		std::vector<Ref<Material>> m_Materials;
		String m_Directory;
		String m_RelativePath;
		LoadedTextures m_LoadedTextures;
		std::map<String, BoneInfo> m_BoneInfoMap;
		int m_BoneCounter;
	};
}