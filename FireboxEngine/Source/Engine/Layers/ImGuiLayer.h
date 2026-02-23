#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Layers/Layer.h"
#include "SDL3/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

namespace Firebox {

	class FIREBOX_API ImGuiLayer : public Layer
	{
	private:
		ImGuiIO* io;
		bool showFolderButton = true;
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