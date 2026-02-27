// Engine/Events/Event.h
#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Input/KeyCodes.h"
#include <string>

namespace Firebox {

    enum class EventType
    {
        None = 0,
        // Window
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        // App
        AppTick, AppUpdate, AppRender,
        // Keyboard
        KeyPressed, KeyReleased, KeyTyped,
        // Mouse
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class EventCategory : uint32_t
    {
        None = 0,
        Application = 1 << 0,
        Input = 1 << 1,
        Keyboard = 1 << 2,
        Mouse = 1 << 3,
        MouseButton = 1 << 4
    };

    inline EventCategory operator|(EventCategory a, EventCategory b)
    {
        return static_cast<EventCategory>(
            static_cast<uint32_t>(a) | static_cast<uint32_t>(b)
            );
    }

    inline bool operator&(EventCategory a, EventCategory b)
    {
        return static_cast<uint32_t>(a) & static_cast<uint32_t>(b);
    }

#define EVENT_CLASS_TYPE(type) \
        static EventType GetStaticType() { return EventType::type; } \
        virtual EventType GetEventType() const override { return GetStaticType(); } \
        virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
        virtual EventCategory GetCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType     GetEventType()      const = 0;
        virtual const char* GetName()           const = 0;
        virtual EventCategory GetCategoryFlags()  const = 0;
        virtual std::string   ToString()          const { return GetName(); }

        bool IsInCategory(EventCategory category) const
        {
            return GetCategoryFlags() & category;
        }
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event) : m_Event(event) {}

        template<typename T, typename Func>
        bool Dispatch(const Func& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };
}