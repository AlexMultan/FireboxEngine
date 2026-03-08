#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Input/KeyCodes.h"
#include "Engine/Input/MouseCodes.h"

#include "glm/glm.hpp"

namespace Firebox {

	class FIREBOX_API Input
	{
	public:
		inline static uint8 s_PreviousKeyState[SDL_SCANCODE_COUNT];

		inline static void OnInputUpdate()
		{
			const bool* currentKeyState = SDL_GetKeyboardState(nullptr);
			
			for (int i = 0; i < SDL_SCANCODE_COUNT; i++)
			{
				s_PreviousKeyState[i] = static_cast<uint8>(currentKeyState[i]);
			}
			SDL_PumpEvents();
			currentKeyState = SDL_GetKeyboardState(nullptr);
		}

		inline static bool IsKeyDown(KeyCode keycode)
		{
			const bool* currentKeyState = SDL_GetKeyboardState(nullptr);
			return currentKeyState[keycode];
		}

		inline static bool IsKeyClicked(KeyCode keycode)
		{
			const bool* currentKeyState = SDL_GetKeyboardState(nullptr);
			return currentKeyState[keycode] && !s_PreviousKeyState[keycode];
		}

		inline static bool IsKeyUp(KeyCode keycode)
		{
			const bool* currentKeyState = SDL_GetKeyboardState(nullptr);
			return currentKeyState[keycode] == 0 && s_PreviousKeyState[keycode] == 1;
		}

		inline static bool IsMouseButtonDown(MouseCode mouseCode)
		{
			return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MASK(mouseCode);
		}

		inline static glm::vec2 GetMousePosition()
		{
			float x, y;
			SDL_GetMouseState(&x, &y);
			return glm::vec2(x, y);
		}

	};
}