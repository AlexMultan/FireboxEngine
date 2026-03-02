#pragma once

#include "Engine/Core/Core.h"
#include "imgui.h"
#include "Editor/Panels/IPanel.h"
#include "glm/glm.hpp"
#include <string>

namespace FireboxEditor {

	class PropertiesPanel : public IPanel
	{
	private:
		std::string m_Name = "Properties";
		glm::vec3 m_PositionParameter = glm::vec3(20.0f, 30.0f, 0.0f);
		glm::vec3 m_RotationParameter = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_ScaleParameter = glm::vec3(1.0f, 1.0f, 1.0f);
		float m_DragStrength = 1.0f;

	public:
		PropertiesPanel();
		PropertiesPanel(const char* name);
		~PropertiesPanel();

		virtual void RenderPanel() override;

		void SetDragStrangth(const float& strength);
	};
}