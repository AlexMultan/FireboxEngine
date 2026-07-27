#pragma once

#include "Animation.h"

namespace Firebox {

	class FIREBOX_API Animator
	{
	public:
		Animator(Animation* animation);
		void Update(float deltaTime);
		void PlayAnimation(Animation* animation);
		void CalculateBoneTransform(const AssimpNodeData* node, Mat4 parentTransform);
		DynamicArray<Mat4> GetFinalBoneMatrices() { return m_FinalBoneMatrices; }

	private:
		DynamicArray<Mat4> m_FinalBoneMatrices;
		Animation* m_CurrentAnimation;
		float m_CurrentTime;
		float m_DeltaTime;
	};
}