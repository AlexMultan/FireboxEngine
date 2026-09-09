#include "Bone.h"
#include "Utils/AssimpHelpers.h"
#include "Utils/Assert.h"

Firebox::Bone::Bone(const String& name, int id, const aiNodeAnim* channel) : m_Name(name), m_Id(id), m_LocalTransform(1.0f)
{
	m_NumPositions = channel->mNumPositionKeys;
	for (int posId = 0; posId < m_NumPositions; posId++)
	{
		aiVector3D aiPos = channel->mPositionKeys[posId].mValue;
		float timeStamp = channel->mPositionKeys[posId].mTime;
		KeyPosition posData{};
		posData.Position = Firebox::AssimpHelpers::GetGlmVec(aiPos);
		posData.TimeStamp = timeStamp;
		m_Positions.emplace_back(posData);
	}

	m_NumRotations = channel->mNumRotationKeys;
	for (int rotationId = 0; rotationId < m_NumRotations; rotationId++)
	{
		aiQuaternion aiOrientation = channel->mRotationKeys[rotationId].mValue;
		float timeStamp = channel->mRotationKeys[rotationId].mTime;
		KeyRotation rotationData{};
		rotationData.Orientation = Firebox::AssimpHelpers::GetGlmQuat(aiOrientation);
		rotationData.TimeStamp = timeStamp;
		m_Rotations.emplace_back(rotationData);
	}

	m_NumScalings = channel->mNumScalingKeys;
	for (int scaleKeyId = 0; scaleKeyId < m_NumScalings; scaleKeyId++)
	{
		aiVector3D aiScale = channel->mScalingKeys[scaleKeyId].mValue;
		float timeStamp = channel->mScalingKeys[scaleKeyId].mTime;
		KeyScale scaleData{};
		scaleData.Scale = Firebox::AssimpHelpers::GetGlmVec(aiScale);
		scaleData.TimeStamp = timeStamp;
		m_Scales.emplace_back(scaleData);
	}
}

void Firebox::Bone::Update(float animTime)
{
	Mat4x4 translation = InterpolatePosition(animTime);
	Mat4x4 rotation = InterpolateRotation(animTime);
	Mat4x4 scale = InterpolateScaling(animTime);
	m_LocalTransform = translation * rotation * scale;
}

int Firebox::Bone::GetPositionIndex(float animTime)
{
	for (int i = 0; i < m_NumPositions - 1; i++)
		if (animTime < m_Positions[static_cast<std::vector<Firebox::KeyPosition, std::allocator<Firebox::KeyPosition>>::size_type>(i) + 1].TimeStamp)
			return i;
}

int Firebox::Bone::GetRotationIndex(float animTime)
{
	for (int i = 0; i < m_NumRotations - 1; i++)
		if (animTime < m_Rotations[static_cast<std::vector<Firebox::KeyRotation, std::allocator<Firebox::KeyRotation>>::size_type>(i) + 1].TimeStamp)
			return i;
}

int Firebox::Bone::GetScaleIndex(float animTime)
{
	for (int i = 0; i < m_NumScalings - 1; i++)
		if (animTime < m_Scales[static_cast<std::vector<Firebox::KeyScale, std::allocator<Firebox::KeyScale>>::size_type>(i) + 1].TimeStamp)
			return i;
}

float Firebox::Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animTime)
{
	float midWayLength = animTime - lastTimeStamp;
	float framesDiff = nextTimeStamp - lastTimeStamp;
	return midWayLength / framesDiff;
}

Mat4x4 Firebox::Bone::InterpolatePosition(float animTime)
{
	if (1 == m_NumPositions)
		return glm::translate(Mat4x4(1.0f), m_Positions[0].Position);

	int p0 = GetPositionIndex(animTime);
	int p1 = p0 + 1;
	Vector3 finalPos = glm::mix(m_Positions[p0].Position, m_Positions[p1].Position, 
		GetScaleFactor(m_Positions[p0].TimeStamp, m_Positions[p1].TimeStamp, animTime));
	return glm::translate(Mat4x4(1.0f), finalPos);
}

Mat4x4 Firebox::Bone::InterpolateRotation(float animTime)
{
	if (1 == m_NumRotations)
	{
		auto rotaion = glm::normalize(m_Rotations[0].Orientation);
		return glm::toMat4(rotaion);
	}

	int r0 = GetRotationIndex(animTime);
	int r1 = r0 + 1;

	Quat finalRotation = glm::slerp(m_Rotations[r0].Orientation, m_Rotations[r1].Orientation,
		GetScaleFactor(m_Rotations[r0].TimeStamp, m_Rotations[r1].TimeStamp, animTime));
	finalRotation = glm::normalize(finalRotation);
	return glm::toMat4(finalRotation);
}

Mat4x4 Firebox::Bone::InterpolateScaling(float animTime)
{
	if (1 == m_NumScalings)
		return glm::scale(Mat4x4(1.0f), m_Scales[0].Scale);

	int s0 = GetScaleIndex(animTime);
	int s1 = s0 + 1;
	Vector3 finalScale = glm::mix(m_Scales[s0].Scale, m_Scales[s1].Scale,
		GetScaleFactor(m_Scales[s0].TimeStamp, m_Scales[s1].TimeStamp, animTime));
	return glm::scale(Mat4x4(1.0f), finalScale);
}
