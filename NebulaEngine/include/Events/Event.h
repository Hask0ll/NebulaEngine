#pragma once

#include <format>

#include "Core/Core.h"
#include "fmt/core.h"
#include <string>
#include <ostream>
#include <functional>

namespace Nebula
{
	/**
	 * \brief Enum class representing different types of events.
	 */
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	 * \brief Enum representing different categories of events.
	 */
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	/**
	 * \brief Macro to define the static type function for an event.
	 *
	 * This macro defines a static function to get the event type, a virtual function to return the event type,
	 * and a function to return the name of the event.
	 */
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return #type; }

	/**
	 * \brief Macro to define the category flags for an event.
	 *
	 * This macro defines a virtual function that returns the category flags for the event.
	 */
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/**
	 * \brief Base class for all events in the engine.
	 *
	 * This class provides the interface for all events. It includes methods for getting the event type,
	 * event name, category flags, and for checking if the event is handled.
	 */
	class NEBULA Event
	{
		friend class EventDispatcher;

	public:
		/**
		 * \brief Get the type of the event.
		 * \return The EventType of the event.
		 */
		virtual EventType GetEventType() const = 0;

		/**
		 * \brief Get the name of the event.
		 * \return The name of the event as a const char*.
		 */
		virtual const char* GetName() const = 0;

		/**
		 * \brief Get the category flags of the event.
		 * \return The category flags as an integer.
		 */
		virtual int GetCategoryFlags() const = 0;

		/**
		 * \brief Convert the event to a string.
		 * \return The event as a std::string.
		 */
		virtual std::string ToString() const { return GetName(); }

		/**
		 * \brief Check if the event is in a specific category.
		 * \param category The category to check against.
		 * \return true if the event is in the category, false otherwise.
		 */
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		/**
		 * \brief Check if the event has been handled.
		 * \return true if the event has been handled, false otherwise.
		 */
		inline bool IsHandled() const { return m_Handled; }

	protected:
		bool m_Handled = false; /**< Indicates whether the event has been handled. */
	};

	/**
	 * \brief Dispatcher for events.
	 *
	 * This class is responsible for dispatching events to the appropriate handlers based on the event type.
	 */
	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		/**
		 * \brief Construct an EventDispatcher for a specific event.
		 * \param event The event to be dispatched.
		 */
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		/**
		 * \brief Dispatch the event if it matches the specified type.
		 *
		 * This template function checks if the event matches the type T, and if so,
		 * it calls the provided function to handle the event.
		 *
		 * \param func The function to handle the event.
		 * \return true if the event was dispatched and handled, false otherwise.
		 */
		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event; /**< Reference to the event being dispatched. */
	};

	/**
	 * \brief Overload the << operator to allow easy logging of events.
	 *
	 * This function converts the event to a string and outputs it to the provided ostream.
	 *
	 * \param os The output stream.
	 * \param e The event to be output.
	 * \return The output stream.
	 */
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

template <>
struct fmt::formatter<Nebula::Event>
{
	constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

	template <typename FormatContext>
	auto format(const Nebula::Event& e, FormatContext& ctx)
	{
		return fmt::format_to(ctx.out(), "{}", e.ToString());
	}
};
