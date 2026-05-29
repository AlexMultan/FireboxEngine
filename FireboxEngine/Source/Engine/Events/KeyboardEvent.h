#pragma once

#include "Engine/Events/Event.h"

namespace Firebox {

    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)

    protected:
        KeyEvent(KeyCode keyCode) : m_KeyCode(keyCode) {}
        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(KeyCode keyCode, bool isRepeat = false)
            : KeyEvent(keyCode), m_IsRepeat(isRepeat)
        {
        }

        bool IsRepeat() const { return m_IsRepeat; }

        String ToString() const override
        {
            return "KeyPressedEvent: " + std::to_string((int)m_KeyCode) +
                (m_IsRepeat ? " (repeat)" : "");
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool m_IsRepeat;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(KeyCode keyCode) : KeyEvent(keyCode) {}

        String ToString() const override
        {
            return "KeyReleasedEvent: " + std::to_string((int)m_KeyCode);
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(KeyCode keyCode) : KeyEvent(keyCode) {}

        EVENT_CLASS_TYPE(KeyTyped)
    };
}