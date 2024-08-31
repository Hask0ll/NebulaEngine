#pragma once

#include "Event.h"        // Project-specific includes
#include <sstream>        // Standard library includes

namespace Nebula {

	/**
	 * \brief Base class for all keyboard events.
	 *
	 * This class is the base for all keyboard-related events and provides
	 * common functionality such as retrieving the key code.
	 */
	class NEBULA KeyEvent : public Event
	{
	public:
		/**
		 * \brief Get the key code associated with the event.
		 * \return The key code as an integer.
		 */
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		/**
		 * \brief Constructor for KeyEvent.
		 * \param keycode The key code associated with the event.
		 */
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode; /**< The key code associated with the event. */
	};

	/**
	 * \brief Event for a key press.
	 *
	 * This event is triggered when a key is pressed. It includes the key code
	 * and the repeat count (how many times the key is repeated while held down).
	 */
	class NEBULA KeyPressedEvent : public KeyEvent
	{
	public:
		/**
		 * \brief Constructor for KeyPressedEvent.
		 * \param keycode The key code of the pressed key.
		 * \param repeatCount The number of times the key is repeated while held down.
		 */
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		/**
		 * \brief Get the number of times the key is repeated while held down.
		 * \return The repeat count as an integer.
		 */
		inline int GetRepeatCount() const { return m_RepeatCount; }

		/**
		 * \brief Convert the event to a string for logging or debugging.
		 * \return A string representation of the event.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	private:
		int m_RepeatCount; /**< The number of times the key is repeated while held down. */
	};

	/**
	 * \brief Event for a key release.
	 *
	 * This event is triggered when a key is released. It includes the key code of the released key.
	 */
	class NEBULA KeyReleasedEvent : public KeyEvent
	{
	public:
		/**
		 * \brief Constructor for KeyReleasedEvent.
		 * \param keycode The key code of the released key.
		 */
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		/**
		 * \brief Convert the event to a string for logging or debugging.
		 * \return A string representation of the event.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};
}
