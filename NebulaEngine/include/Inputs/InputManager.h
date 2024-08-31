#pragma once

#include <utility>  // For std::pair

#include "Core/Core.h"

namespace Nebula
{
	/**
	 * \brief Abstract base class for handling input.
	 *
	 * The Input class provides an interface for querying keyboard and mouse state, such as whether a key or mouse button is pressed
	 * or the current position of the mouse. Platform-specific implementations of this class must define the actual behavior.
	 */
	class NEBULA Input
	{
	public:
		/**
		 * \brief Check if a specific key is pressed.
		 * \param keycode The keycode of the key to check.
		 * \return True if the key is pressed, false otherwise.
		 */
		[[nodiscard]] static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		/**
		 * \brief Check if a specific mouse button is pressed.
		 * \param button The button code of the mouse button to check.
		 * \return True if the mouse button is pressed, false otherwise.
		 */
		[[nodiscard]] static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		/**
		 * \brief Get the current position of the mouse.
		 * \return A pair containing the x and y coordinates of the mouse position.
		 */
		[[nodiscard]] static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

		/**
		 * \brief Get the current x-coordinate of the mouse.
		 * \return The x-coordinate of the mouse position.
		 */
		[[nodiscard]] static float GetMouseX() { return s_Instance->GetMouseXImpl(); }

		/**
		 * \brief Get the current y-coordinate of the mouse.
		 * \return The y-coordinate of the mouse position.
		 */
		[[nodiscard]] static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		/**
		 * \brief Check if a specific key is pressed (platform-specific implementation).
		 * \param keycode The keycode of the key to check.
		 * \return True if the key is pressed, false otherwise.
		 */
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		/**
		 * \brief Check if a specific mouse button is pressed (platform-specific implementation).
		 * \param button The button code of the mouse button to check.
		 * \return True if the mouse button is pressed, false otherwise.
		 */
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		/**
		 * \brief Get the current x-coordinate of the mouse (platform-specific implementation).
		 * \return The x-coordinate of the mouse position.
		 */
		virtual float GetMouseXImpl() = 0;

		/**
		 * \brief Get the current y-coordinate of the mouse (platform-specific implementation).
		 * \return The y-coordinate of the mouse position.
		 */
		virtual float GetMouseYImpl() = 0;

		/**
		 * \brief Get the current position of the mouse (platform-specific implementation).
		 * \return A pair containing the x and y coordinates of the mouse position.
		 */
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		/** \brief A pointer to the platform-specific input implementation. */
		static Input* s_Instance;
	};
}
