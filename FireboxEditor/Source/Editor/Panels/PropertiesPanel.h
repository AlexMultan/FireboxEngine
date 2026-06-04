#pragma once

#include "Engine/Core/Core.h"
#include "Editor/Panels/IPanel.h"

#include <imgui.h>

namespace FireboxEditor {

	class PropertiesPanel : public IPanel
	{
	private:
		String m_Name = "Properties";
		Vector3 m_PositionParameter = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 m_RotationParameter = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 m_ScaleParameter = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 m_LightDirectionParameter = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 m_LightPositionParameter = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 m_CubeColorParameter;
		float m_CubeSpecularParameter;
		float m_DragStrength = 0.2f;
		ImFont* m_TransformPropertiesFont = nullptr;

	public:
		PropertiesPanel();
		PropertiesPanel(const char* name);
		~PropertiesPanel();

		virtual void RenderPanel() override;

		void SetDragStrangth(const float& strength);
		void PushTreeNodeStyle();
		void PopTreeNodeStyle();

		inline const Vector3& GetPositionParameter() const
		{
			return m_PositionParameter;
		}

		inline const Vector3& GetRotationParameter() const
		{
			return m_RotationParameter;
		}

		inline const Vector3& GetScaleParameter() const
		{
			return m_ScaleParameter;
		}

		inline const Vector3& GetLightDirectionParameter() const
		{
			return m_LightDirectionParameter;
		}

		inline const Vector3& GetLightPositionParameter() const
		{
			return m_LightPositionParameter;
		}

		inline const Vector3& GetColorParameter() const
		{
			return m_CubeColorParameter;
		}

		inline const float GetSpecularParameter() const
		{
			return m_CubeSpecularParameter;
		}

		inline void SetPositionParameter(const Vector3& otherVector)
		{
			m_PositionParameter = otherVector;
		}

		inline void SetRotationParameter(const Vector3& otherVector)
		{
			m_RotationParameter = otherVector;
		}

		inline void SetScaleParameter(const Vector3& otherVector)
		{
			m_ScaleParameter = otherVector;
		}

		inline void SetLightDirectionParameter(const Vector3& newDirection)
		{
			m_LightDirectionParameter = newDirection;
		}

		inline void SetLightPositionParameter(const Vector3& newPosition)
		{
			m_LightPositionParameter = newPosition;
		}

		inline void SetTransformPropertiesFont(ImFont* font)
		{
			m_TransformPropertiesFont = font;
		}

		inline void SetColorParameter(const Vector3& otherColor)
		{
			m_CubeColorParameter = otherColor;
		}

		inline void SetSpecularParameter(float specular)
		{
			m_CubeSpecularParameter = specular;
		}
	};
}