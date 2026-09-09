#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"
#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>

namespace Firebox {

	class FIREBOX_API Input
	{
	public:
		inline static uint8 s_PreviousKeyState[SDL_SCANCODE_COUNT];
		inline static SDL_MouseButtonFlags s_PreviousMouseState;
		inline static SDL_MouseButtonFlags s_CurrentMouseState;

		inline static float s_RelativeMouseX = 0.0f;
		inline static float s_RelativeMouseY = 0.0f;
		inline static bool s_IsRelativeMode = false;

		inline static void OnInputUpdate()
		{
			const bool* currentKeyState = SDL_GetKeyboardState(nullptr);
			
			for (int i = 0; i < SDL_SCANCODE_COUNT; i++)
			{
				s_PreviousKeyState[i] = static_cast<uint8>(currentKeyState[i]);
			}

			s_PreviousMouseState = s_CurrentMouseState;
			SDL_PumpEvents();
			s_CurrentMouseState = SDL_GetMouseState(nullptr, nullptr);
			currentKeyState = SDL_GetKeyboardState(nullptr);

			if (s_IsRelativeMode)
			{
				SDL_GetRelativeMouseState(&s_RelativeMouseX, &s_RelativeMouseY);
			}
			else
			{
				s_RelativeMouseX = 0.0f;
				s_RelativeMouseY = 0.0f;
			}
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
			return (s_CurrentMouseState & SDL_BUTTON_MASK(mouseCode)) != 0;
		}

		inline static bool IsMouseButtonClicked(MouseCode mouseCode)
		{
			return (s_CurrentMouseState & SDL_BUTTON_MASK(mouseCode)) != 0 && (s_PreviousMouseState & SDL_BUTTON_MASK(mouseCode)) == 0;
		}

		inline static bool IsMouseButtonUp(MouseCode mouseCode)
		{
			return (s_CurrentMouseState & SDL_BUTTON_MASK(mouseCode)) == 0;
		}

		inline static bool IsMouseButtonReleased(MouseCode mouseCode)
		{
			bool wasDown = (s_PreviousMouseState & SDL_BUTTON_MASK(mouseCode)) != 0;
			bool isDown = (s_CurrentMouseState & SDL_BUTTON_MASK(mouseCode)) != 0;
			return wasDown && !isDown;
		}

		inline static Vector2 GetMousePosition()
		{
			float x, y;
			SDL_GetMouseState(&x, &y);
			return Vector2(x, y);
		}

		inline static void SetRelativeMouseMode(bool enabled)
		{
			s_IsRelativeMode = enabled;
			SDL_SetWindowRelativeMouseMode(SDL_GL_GetCurrentWindow(), enabled);

			s_RelativeMouseX = 0.0f;
			s_RelativeMouseY = 0.0f;
		}

		inline static Vector2 GetMouseDelta()
		{
			return Vector2(s_RelativeMouseX, s_RelativeMouseY);
		}
	};
}