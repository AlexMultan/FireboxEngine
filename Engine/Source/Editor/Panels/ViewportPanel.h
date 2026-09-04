#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"
#include "Rendering/Targets/Framebuffer.h"
#include "Core/EditorContext.h"

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
		ViewportPanel(const char* name, EditorContext& context);
		~ViewportPanel();

		void RenderViewport(const Mat4x4& viewMatrix, const Mat4x4& projectionMatrix);

		inline const Vector2& GetViewportSize() { return m_ViewportSize; }
		inline bool IsFocused() const { return m_IsFocused; }
		inline const float GetCamaraSpeedParam() const { return m_CameraSpeed; }
		inline void SetMenuBarHeight(float height) { m_MenuBarHeight = height; }
		inline const float& GetGridSize() const { return m_GridSize; }
		inline const uint GetViewMode() const { return m_CurrentViewMode; }

	private:
		String m_Name = "Viewport";
		uint m_TextureID;
		Vector2 m_ViewportSize{ 0.0f, 0.0f };
		bool m_IsFocused = false;
		float m_CameraSpeed = 2.0f;
		float m_MenuBarHeight = 0.0f;
		bool m_Snap = true;
		float m_GridSize = 1.0f;
		uint m_CurrentViewMode = 0;
		EditorContext& m_Context;
		Firebox::Entity m_SelectedEntity;

		GizmoTransformType m_GizmoTransformType = GizmoTransformType::Translate;
		GizmoTransformSpace m_GizmoTransformSpace = GizmoTransformSpace::World;
	};
}