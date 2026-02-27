#pragma once

#include <string>
#include "Engine/Core/Core.h"
#include "Engine/Events/Event.h"

namespace Firebox {

	class FIREBOX_API Layer
	{
	protected:
		std::string m_DebugName;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}
		virtual void OnEditorUIRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetLayerName() const 
		{ 
			return m_DebugName; 
		}
	};
}