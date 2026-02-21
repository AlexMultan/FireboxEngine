#pragma once

#include "Core/Core.h"
#include "Layers/Layer.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

namespace Firebox {

	class FIREBOX_API ImGuiLayer : public Layer
	{
	private:
		ImGuiIO* io;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(SDL_Event& event) override;

		void Begin();
		void End();
	};
}