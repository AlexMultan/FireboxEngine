#pragma once

#include "Core/Core.h"

#include <assimp/scene.h>

namespace Firebox {

	struct KeyPosition
	{
		Vector3 Position;
		float TimeStamp;
	};

	struct KeyRotation
	{
		Quat Orientation;
		float TimeStamp;
	};

	struct KeyScale
	{
		Vector3 Scale;
		float TimeStamp;
	};

	class FIREBOX_API Bone
	{
	public:
		Bone(const String& name, int id, const aiNodeAnim* channel);
		void Update(float animTime);

		inline Mat4 GetLocalTransform() { return m_LocalTransform; }
		inline String GetBoneName() const { return m_Name; }
		inline int GetBoneId() { return m_Id; }
		int GetPositionIndex(float animTime);
		int GetRotationIndex(float animTime);
		int GetScaleIndex(float animTime);

	private:
		float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animTime);
		Mat4 InterpolatePosition(float animTime);
		Mat4 InterpolateRotation(float animTime);
		Mat4 InterpolateScaling(float animTime);

	private:
		std::vector<KeyPosition> m_Positions;
		std::vector<KeyRotation> m_Rotations;
		std::vector<KeyScale> m_Scales;
		int m_NumPositions;
		int m_NumRotations;
		int m_NumScalings;

		Mat4 m_LocalTransform;
		String m_Name;
		int m_Id;
	};
}