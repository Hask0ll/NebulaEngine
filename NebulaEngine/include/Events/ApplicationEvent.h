#pragma once

#include <sstream>          // Standard library includes should come first
#include "Core/Core.h"      // Core includes (project-specific) should follow
#include "Event.h"          // Project-specific includes

namespace Nebula {

	/**
	 * \brief Event for window resize.
	 *
	 * This event is triggered when the window is resized. It carries the new width and height of the window.
	 */
	class NEBULA WindowResizeEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for WindowResizeEvent.
		 * \param width The new width of the window.
		 * \param height The new height of the window.
		 */
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		/**
		 * \brief Get the new width of the window.
		 * \return The width of the window.
		 */
		inline unsigned int GetWidth() const { return m_Width; }

		/**
		 * \brief Get the new height of the window.
		 * \return The height of the window.
		 */
		inline unsigned int GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height; /**< The new width and height of the window. */
	};

	/**
	 * \brief Event for window close.
	 *
	 * This event is triggered when the window is requested to close.
	 */
	class NEBULA WindowCloseEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for WindowCloseEvent.
		 */
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * \brief Event for application tick.
	 *
	 * This event is triggered on every tick of the application.
	 */
	class NEBULA AppTickEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for AppTickEvent.
		 */
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * \brief Event for application update.
	 *
	 * This event is triggered every time the application updates.
	 */
	class NEBULA AppUpdateEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for AppUpdateEvent.
		 */
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * \brief Event for application render.
	 *
	 * This event is triggered when the application renders a frame.
	 */
	class NEBULA AppRenderEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for AppRenderEvent.
		 */
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
