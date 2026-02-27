#include "Engine/Input/Input.h"
#include "SDL3/SDL.h"

bool Firebox::Input::IsKeyPressed(KeyCode keycode)
{
    const bool* state = SDL_GetKeyboardState(nullptr);
    return state[keycode];
}

bool Firebox::Input::IsMouseButtonPressed(int button)
{
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MASK(button);
}

float Firebox::Input::GetMouseX()
{
    float x;
    SDL_GetMouseState(&x, nullptr);
    return x;
}

float Firebox::Input::GetMouseY()
{
    float y;
    SDL_GetMouseState(nullptr, &y);
    return y;
}