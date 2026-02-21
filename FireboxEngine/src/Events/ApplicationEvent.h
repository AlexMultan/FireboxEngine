#pragma once

#include "Event.h"

namespace Firebox {

	class FIREBOX_API WindowResizeEvent : public Event
	{
	private:
		unsigned int m_Width, m_Height;

	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height)
		{

		}

		inline unsigned int GetWidth() const
		{
			return m_Width;
		}

		inline unsigned int GetHeight() const
		{
			return m_Height;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApp)

	};

	class FIREBOX_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{

		}

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApp)
	};

	class FIREBOX_API EngineTickEvent : public Event
	{
	public:
		EngineTickEvent()
		{

		}

		EVENT_CLASS_TYPE(EngineTick)
			EVENT_CLASS_CATEGORY(EventCategoryApp)
	};

	class FIREBOX_API EngineUpdateEvent : public Event
	{
	public:
		EngineUpdateEvent()
		{

		}

		EVENT_CLASS_TYPE(EngineUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApp)
	};

	class FIREBOX_API EngineRenderEvent : public Event
	{
	public:
		EngineRenderEvent()
		{

		}

		EVENT_CLASS_TYPE(EngineRender)
			EVENT_CLASS_CATEGORY(EventCategoryApp)
	};