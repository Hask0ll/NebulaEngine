#pragma once

#include "Renderer/VertexArray/VertexArray.h"
#include <cstdint>
#include <glm/glm.hpp>

namespace Nebula
{
    /**
     * @class RendererApi
     * @brief Abstract base class defining the interface for renderer APIs in the Nebula engine.
     *
     * This class provides a common interface for different rendering APIs,
     * allowing for easy switching between rendering backends.
     */
    class RendererApi
    {
    public:
        /**
         * @enum API
         * @brief Enumeration of supported rendering APIs.
         */
        enum class API
        {
            None = 0,  /**< No API selected */
            OpenGl = 1 /**< OpenGL API */
        };

    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived classes.
         */
        virtual ~RendererApi() = default;

        /**
         * @brief Set the clear color for the rendering context.
         * @param color The color to set as clear color.
         */
        virtual void SetClearColor(const glm::vec4& color) = 0;

        /**
         * @brief Clear the current rendering context.
         */
        virtual void Clear() = 0;

        /**
         * @brief Draw indexed geometry.
         * @param vertexArray The vertex array object containing the geometry data.
         * @param indexCount The number of indices to draw. If 0, all indices will be drawn.
         */
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

        /**
         * @brief Get the currently active rendering API.
         * @return API The currently active rendering API.
         */
        static API GetAPI() { return s_API; }

    private:
        inline static API s_API; /**< The currently active rendering API. */
    };
}