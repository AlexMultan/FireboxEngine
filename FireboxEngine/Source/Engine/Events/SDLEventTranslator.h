#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"
#include <SDL3/SDL_events.h>
#include <memory>

namespace Firebox {

    class SDLEventTranslator
    {
    public:
        static Scope<Event> Translate(const SDL_Event& sdlEvent)
        {
            switch (sdlEvent.type)
            {
            case SDL_EVENT_KEY_DOWN:
                return CreateScope<KeyPressedEvent>(
                    static_cast<KeyCode>(sdlEvent.key.key),
                    sdlEvent.key.repeat
                );
            case SDL_EVENT_KEY_UP:
                return CreateScope<KeyReleasedEvent>(
                    static_cast<KeyCode>(sdlEvent.key.key)
                );
            case SDL_EVENT_TEXT_INPUT:
                return CreateScope<KeyTypedEvent>(
                    static_cast<KeyCode>(sdlEvent.text.text[0])
                );

            case SDL_EVENT_MOUSE_MOTION:
                return CreateScope<MouseMovedEvent>(
                    sdlEvent.motion.x, sdlEvent.motion.y
                );
            case SDL_EVENT_MOUSE_WHEEL:
                return CreateScope<MouseScrolledEvent>(
                    sdlEvent.wheel.x, sdlEvent.wheel.y
                );
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                return CreateScope<MouseButtonPressedEvent>(
                    sdlEvent.button.button
                );
            case SDL_EVENT_MOUSE_BUTTON_UP:
                return CreateScope<MouseButtonReleasedEvent>(
                    sdlEvent.button.button
                );

            case SDL_EVENT_WINDOW_RESIZED:
                return CreateScope<WindowResizeEvent>(
                    sdlEvent.window.data1, sdlEvent.window.data2
                );
            case SDL_EVENT_QUIT:
                return CreateScope<WindowCloseEvent>();

            default:
                return nullptr;
            }
        }
    };
}