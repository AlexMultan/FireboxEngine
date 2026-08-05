#include "Animation.h"
#include "Utils/Assert.h"
#include "Utils/AssimpHelpers.h"

// TO-DO: Investigate this class for memory corruption/fragmentation/leaks

Firebox::Animation::Animation(const String& path, const Ref<StaticMesh>& model)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
	auto anim = scene->mAnimations[0];
	m_Duration = anim->mDuration;
	m_TicksPerSecond = anim->mTicksPerSecond;
	ReadHierarchyData(m_RootNode, scene->mRootNode);
	ReadMissingBones(anim, *model);
}

Firebox::Animation::~Animation()
{
}

Firebox::Bone* Firebox::Animation::FindBone(const String& name)
{
	auto iter = std::find_if(m_Bones.begin(), m_Bones.end(), [&](const Bone& bone)
		{
			return bone.GetBoneName() == name;
		});
	if (iter == m_Bones.end())
		return nullptr;
	else
		return &(*iter);
}

void Firebox::Animation::ReadMissingBones(const aiAnimation* animation, StaticMesh& model)
{
	uint size = animation->mNumChannels;
	auto& boneInfo = model.GetBoneInfoMap();
	int& boneCount = model.GetBoneCount();

	for (int i = 0; i < size; i++)
	{
		auto channel = animation->mChannels[i];
		String name = channel->mNodeName.data;

		if (boneInfo.find(name) == boneInfo.end())
		{
			boneInfo[name].Id = boneCount;
			boneCount++;
		}

		m_Bones.emplace_back(Bone(channel->mNodeName.data, boneInfo[channel->mNodeName.data].Id, channel));
	}
	m_BoneInfoMap = boneInfo;
}

void Firebox::Animation::ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
{
	FB_ASSERT(src, "");

	dest.Name = src->mName.data;
	dest.Transformation = Firebox::AssimpHelpers::ConvertMatrixToGlmFormat(src->mTransformation);
	dest.ChildrenCount = src->mNumChildren;

	for (uint i = 0; i < src->mNumChildren; i++)
	{
		AssimpNodeData newData;
		ReadHierarchyData(newData, src->mChildren[i]);
		dest.Children.emplace_back(newData);
	}
}
