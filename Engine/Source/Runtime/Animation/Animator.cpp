#include "Animator.h"
#include "Utils/Assert.h"

Firebox::Animator::Animator(Animation* animation) : m_CurrentTime(0.0f), m_DeltaTime(0.0f), m_CurrentAnimation(nullptr)
{
	m_CurrentAnimation = animation;
	m_FinalBoneMatrices.reserve(100);

	for (uint i = 0; i < 100; i++)
		m_FinalBoneMatrices.emplace_back(Mat4(1.0f));
}

void Firebox::Animator::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;
	if (m_CurrentAnimation)
	{
		m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * deltaTime;
		m_CurrentTime = std::fmod(m_CurrentTime, m_CurrentAnimation->GetDuration());
		CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), Mat4(1.0f));
	}	
}

void Firebox::Animator::PlayAnimation(Animation* animation)
{
	m_CurrentAnimation = animation;
	m_CurrentTime = 0.0f;
}

void Firebox::Animator::CalculateBoneTransform(const AssimpNodeData* node, Mat4 parentTransform)
{
	String nodeName = node->Name;
	Mat4 nodeTransform = node->Transformation;
	Bone* bone = m_CurrentAnimation->FindBone(nodeName);

	if (bone)
	{
		bone->Update(m_CurrentTime);
		nodeTransform = bone->GetLocalTransform();
	}

	Mat4 globalTransform = parentTransform * nodeTransform;

	auto boneInfo = m_CurrentAnimation->GetBoneIdMap();
	if (boneInfo.find(nodeName) != boneInfo.end())
	{
		int id = boneInfo[nodeName].Id;
		Mat4 offset = boneInfo[nodeName].Offset;
		if (id < 0 || id >= (int)m_FinalBoneMatrices.size())
		{
			FB_ASSERT(true, "Bone id {} out of range for node '{}' (matrices size = {})", id, nodeName, m_FinalBoneMatrices.size());
		}
		else
			m_FinalBoneMatrices[id] = globalTransform * offset;
	}

	for (int i = 0; i < node->ChildrenCount; i++)
		CalculateBoneTransform(&node->Children[i], globalTransform);
}
