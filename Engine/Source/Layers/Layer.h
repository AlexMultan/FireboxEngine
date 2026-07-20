#pragma once

#include <string>
#include "Core/Core.h"
#include "Events/Event.h"

namespace Firebox {

	class FIREBOX_API Layer
	{
	protected:
		String m_DebugName;
	public:
		Layer(const String& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender(float deltaTime) {}
		virtual void OnEditorUIRender() {}
		virtual void OnEvent(Event& event) {}

		inline const String& GetLayerName() const 
		{ 
			return m_DebugName; 
		}
	};
}