#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Rendering/Resources/Framebuffer.h"
#include "Engine/Components/Components.h"

namespace FireboxEditor {

	enum class GizmoTransformType : uint
	{
		Translate = 0,
		Rotate = 1,
		Scale = 2
	};

	enum class GizmoTransformSpace : uint
	{
		Local = 0,
		World = 1
	};

	class ViewportPanel
	{
	public:
		ViewportPanel();
		ViewportPanel(const char* name);
		~ViewportPanel();

		void RenderViewport(const Ref<Firebox::Framebuffer>& framebuffer, const Mat4& viewMatrix, const Mat4& projectionMatrix, 
			TransformComponent& transformComp);

		inline const Vector2& GetViewportSize() { return m_ViewportSize; }
		inline bool IsFocused() const { return m_IsFocused; }
		inline const float GetCamaraSpeedParam() const { return m_CameraSpeed; }
		inline void SetMenuBarHeight(float height) { m_MenuBarHeight = height; }
		inline const float& GetGridSize() const { return m_GridSize; }

	private:
		String m_Name = "Viewport";
		uint m_TextureID;
		Vector2 m_ViewportSize{ 0.0f, 0.0f };
		bool m_IsFocused = false;
		float m_CameraSpeed = 2.0f;
		float m_MenuBarHeight = 0.0f;
		bool m_Snap = true;
		float m_GridSize = 1.0f;

		GizmoTransformType m_GizmoTransformType = GizmoTransformType::Translate;
		GizmoTransformSpace m_GizmoTransformSpace = GizmoTransformSpace::World;
	};
}