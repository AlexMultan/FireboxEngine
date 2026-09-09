#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

namespace Firebox {

	struct SSAOInfo
	{
		uint Width;
		uint Height;
	};

	class FIREBOX_API SSAO : public RefCounted
	{
	public:
		virtual ~SSAO() = default;

		virtual void BindSSAOBuffer() = 0;
		virtual void UnbindSSAOBuffer() = 0;
		virtual void BindSSAOBlurBuffer() = 0;
		virtual void UnbindSSAOBlurBuffer() = 0;
		virtual void ResizeSSAOBuffer(uint width, uint height) = 0;
		virtual void GenerateNoiseTexture();
		virtual void BindNoiseTexture() = 0;
		virtual void BindSSAOTexture() = 0;
		virtual void BindSSAOBlurTexture() = 0;
		void GenerateSampleKernel();

		inline const std::vector<Vector3>& GetKernel() const { return m_SSAOKernel; }

		static Ref<SSAO> Create();

	protected:
		std::vector<Vector3> m_SSAONoise;
		std::vector<Vector3> m_SSAOKernel;
	};
}