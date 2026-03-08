#pragma once

#include <string>
#include "Engine/Core/Core.h"
#include "Engine/Events/Event.h"

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
		virtual void OnUpdate() {}
		virtual void OnRender() {}
		virtual void OnEditorUIRender() {}
		virtual void OnEvent(Event& event) {}

		inline const String& GetLayerName() const 
		{ 
			return m_DebugName; 
		}
	};
}