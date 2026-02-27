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
        static std::unique_ptr<Event> Translate(const SDL_Event& sdlEvent)
        {
            switch (sdlEvent.type)
            {
            case SDL_EVENT_KEY_DOWN:
                return std::make_unique<KeyPressedEvent>(
                    static_cast<KeyCode>(sdlEvent.key.key),
                    sdlEvent.key.repeat
                );
            case SDL_EVENT_KEY_UP:
                return std::make_unique<KeyReleasedEvent>(
                    static_cast<KeyCode>(sdlEvent.key.key)
                );
            case SDL_EVENT_TEXT_INPUT:
                return std::make_unique<KeyTypedEvent>(
                    static_cast<KeyCode>(sdlEvent.text.text[0])
                );

            case SDL_EVENT_MOUSE_MOTION:
                return std::make_unique<MouseMovedEvent>(
                    sdlEvent.motion.x, sdlEvent.motion.y
                );
            case SDL_EVENT_MOUSE_WHEEL:
                return std::make_unique<MouseScrolledEvent>(
                    sdlEvent.wheel.x, sdlEvent.wheel.y
                );
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                return std::make_unique<MouseButtonPressedEvent>(
                    sdlEvent.button.button
                );
            case SDL_EVENT_MOUSE_BUTTON_UP:
                return std::make_unique<MouseButtonReleasedEvent>(
                    sdlEvent.button.button
                );

            case SDL_EVENT_WINDOW_RESIZED:
                return std::make_unique<WindowResizeEvent>(
                    sdlEvent.window.data1, sdlEvent.window.data2
                );
            case SDL_EVENT_QUIT:
                return std::make_unique<WindowCloseEvent>();

            default:
                return nullptr;
            }
        }
    };
}