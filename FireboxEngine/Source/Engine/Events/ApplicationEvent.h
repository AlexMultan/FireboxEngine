#pragma once

#include "Engine/Events/Event.h"

namespace Firebox {

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint width, uint height)
            : m_Width(width), m_Height(height)
        {
        }

        uint GetWidth()  const { return m_Width; }
        uint GetHeight() const { return m_Height; }

        EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategory::Application)

    private:
        uint m_Width, m_Height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategory::Application)
    };
}