#pragma once

#include "Mesh.h"
#include "Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Firebox {

	class FIREBOX_API StaticMesh
	{
	public:
		StaticMesh(const String& path);

		const DynamicArray<Ref<Mesh>>& GetMeshes() const { return m_Meshes; }
		//const DynamicArray<Ref<Material>>& GetMaterials() const { return m_Materials; }
	private:

		DynamicArray<Ref<Mesh>> m_Meshes;
		//DynamicArray<Ref<Material>> m_Materials;
		String m_Directory;

		void ProcessNode(aiNode* node, const aiScene* scene);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}