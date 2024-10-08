#pragma once

#include "Renderer/Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Nebula
{
    /**
     * @class OpenGLContext
     * @brief Represents an OpenGL rendering context in the Nebula engine.
     *
     * This class implements the GraphicsContext interface for OpenGL,
     * providing initialization and buffer swapping functionality.
     */
    class OpenGLContext final : public GraphicsContext
    {
    public:
        /**
         * @brief Construct a new OpenGLContext object.
         * @param windowHandle Pointer to the GLFW window handle.
         */
        explicit OpenGLContext(GLFWwindow* windowHandle);

        /**
         * @brief Destroy the OpenGLContext object.
         */
        ~OpenGLContext() override = default;

        /**
         * @brief Initialize the OpenGL context.
         *
         * This method sets up the OpenGL context for rendering.
         */
        void Init() override;

        /**
         * @brief Swap the front and back buffers.
         *
         * This method presents the rendered content to the screen.
         */
        void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle; /**< Pointer to the GLFW window handle. */
    };
}