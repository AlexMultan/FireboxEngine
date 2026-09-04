#pragma once

#include "Bone.h"
#include "Rendering/Geometry/StaticMesh.h"

namespace Firebox {

	struct AssimpNodeData
	{
		Mat4x4 Transformation;
		String Name;
		int ChildrenCount;
		std::vector<AssimpNodeData> Children;
	};

	class FIREBOX_API Animation
	{
	public:
		Animation() = default;
		Animation(const String& path, const Ref<StaticMesh>& model);
		~Animation();
		
		Bone* FindBone(const String& name);
		inline float GetTicksPerSecond() { return m_TicksPerSecond; }
		inline const float GetDuration() const { return m_Duration; }
		inline const AssimpNodeData& GetRootNode() const { return m_RootNode; }
		inline const std::map<String, BoneInfo>& GetBoneIdMap() const { return m_BoneInfoMap; }

	private:
		void ReadMissingBones(const aiAnimation* animation, StaticMesh& model);
		void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);

	private:
		float m_TicksPerSecond;
		float m_Duration;
		std::vector<Bone> m_Bones;
		AssimpNodeData m_RootNode;
		std::map<String, BoneInfo> m_BoneInfoMap;
	};
}