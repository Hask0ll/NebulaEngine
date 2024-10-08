#pragma once

#include <utility>
#include "Inputs/InputManager.h"

namespace Nebula
{
    /**
     * @class WindowsInput
     * @brief Implements the Input interface for Windows platform in the Nebula engine.
     *
     * This class provides Windows-specific implementations for input-related functions
     * such as keyboard and mouse input.
     */
    class WindowsInput final : public Input
    {
    protected:
        /**
         * @brief Check if a specific key is pressed.
         * @param keycode The keycode of the key to check.
         * @return bool True if the key is pressed, false otherwise.
         */
        bool IsKeyPressedImpl(int keycode) override;

        /**
         * @brief Check if a specific mouse button is pressed.
         * @param button The button code to check.
         * @return bool True if the mouse button is pressed, false otherwise.
         */
        bool IsMouseButtonPressedImpl(int button) override;

        /**
         * @brief Get the current X coordinate of the mouse cursor.
         * @return float The X coordinate of the mouse cursor.
         */
        float GetMouseXImpl() override;

        /**
         * @brief Get the current Y coordinate of the mouse cursor.
         * @return float The Y coordinate of the mouse cursor.
         */
        float GetMouseYImpl() override;

        /**
         * @brief Get the current position of the mouse cursor.
         * @return std::pair<float, float> A pair containing the X and Y coordinates of the mouse cursor.
         */
        std::pair<float, float> GetMousePositionImpl() override;
    };
}