#pragma once

#include "Engine/Core/Core.h"
#include "Editor/Panels/IPanel.h"

namespace FireboxEditor {

	class PropertiesPanel : public IPanel
	{
	private:
		String m_Name = "Properties";
		Vector3 m_PositionParameter = Vector3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_RotationParameter = Vector3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_ScaleParameter = glm::vec3(1.0f, 1.0f, 1.0f);
		float m_DragStrength = 0.05f;

	public:
		PropertiesPanel();
		PropertiesPanel(const char* name);
		~PropertiesPanel();

		virtual void RenderPanel() override;

		void SetDragStrangth(const float& strength);

		inline const Vector3& GetPositionParameter() const
		{
			return m_PositionParameter;
		}
	};
}