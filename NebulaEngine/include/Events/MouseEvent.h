#pragma once

#include "Event.h"        // Project-specific includes

#include <string>         // Standard library includes
#include <sstream>        // Standard library includes

namespace Nebula {

	/**
	 * \brief Event triggered when the mouse is moved.
	 *
	 * This event captures the new position of the mouse when it is moved.
	 */
	class MouseMovedEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for MouseMovedEvent.
		 * \param x The new x-coordinate of the mouse.
		 * \param y The new y-coordinate of the mouse.
		 */
		MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}

		/**
		 * \brief Get the x-coordinate of the mouse.
		 * \return The x-coordinate as a float.
		 */
		float GetX() const { return m_MouseX; }

		/**
		 * \brief Get the y-coordinate of the mouse.
		 * \return The y-coordinate as a float.
		 */
		float GetY() const { return m_MouseY; }

		/**
		 * \brief Convert the event to a string for logging or debugging.
		 * \return A string representation of the event.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY; /**< The x and y coordinates of the mouse. */
	};

	/**
	 * \brief Event triggered when the mouse wheel is scrolled.
	 *
	 * This event captures the offset of the scroll wheel in the x and y directions.
	 */
	class MouseScrolledEvent : public Event
	{
	public:
		/**
		 * \brief Constructor for MouseScrolledEvent.
		 * \param xOffset The horizontal scroll offset.
		 * \param yOffset The vertical scroll offset.
		 */
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		/**
		 * \brief Get the horizontal scroll offset.
		 * \return The horizontal scroll offset as a float.
		 */
		float GetXOffset() const { return m_XOffset; }

		/**
		 * \brief Get the vertical scroll offset.
		 * \return The vertical scroll offset as a float.
		 */
		float GetYOffset() const { return m_YOffset; }

		/**
		 * \brief Convert the event to a string for logging or debugging.
		 * \return A string representation of the event.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset; /**< The scroll offsets in the x and y directions. */
	};

	/**
	 * \brief Base class for mouse button events.
	 *
	 * This class serves as the base for events related to mouse buttons, providing common functionality.
	 */
	class MouseButtonEvent : public Event
	{
	public:
		/**
		 * \brief Get the mouse button associated with the event.
		 * \return The mouse button as an integer.
		 */
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		/**
		 * \brief Constructor for MouseButtonEvent.
		 * \param button The mouse button associated with the event.
		 */
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button; /**< The mouse button associated with the event. */
	};

	/**
	 * \brief Event triggered when a mouse button is pressed.
	 *
	 * This event captures the mouse button that was pressed.
	 */
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		/**
		 * \brief Constructor for MouseButtonPressedEvent.
		 * \param button The mouse button that was pressed.
		 */
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		/**
		 * \brief Convert the event to a string for logging or debugging.
		 * \return A string representation of the event.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/**
	 * \brief Event triggered when a mouse button is released.
	 *
	 * This event captures the mouse button that was released.
	 */
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		/**
		 * \brief Constructor for MouseButtonReleasedEvent.
		 * \param button The mouse button that was released.
		 */
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		/**
		 * \brief Convert the event to a string for logging or debugging.
		 * \return A string representation of the event.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
