#pragma once

#include "Renderer/VertexArray/VertexArray.h"
#include <memory>
#include <vector>

namespace Nebula
{
    /**
     * @class OpenGLVertexArray
     * @brief Represents an OpenGL vertex array object in the Nebula engine.
     *
     * This class implements the VertexArray interface for OpenGL,
     * managing vertex and index buffers for rendering.
     */
    class NEBULA OpenGLVertexArray final : public VertexArray
    {
    public:
        /**
         * @brief Construct a new OpenGLVertexArray object.
         */
        OpenGLVertexArray();

        /**
         * @brief Destroy the OpenGLVertexArray object.
         */
        ~OpenGLVertexArray() override = default;

        /**
         * @brief Bind the vertex array object.
         */
        void Bind() const override;

        /**
         * @brief Unbind the vertex array object.
         */
        void UnBind() const override;

        /**
         * @brief Add a vertex buffer to the vertex array.
         * @param vertexBuffer Shared pointer to the VertexBuffer to be added.
         */
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

        /**
         * @brief Set the index buffer for the vertex array.
         * @param indexBuffer Shared pointer to the IndexBuffer to be set.
         */
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        /**
         * @brief Get the vector of vertex buffers.
         * @return const std::vector<std::shared_ptr<VertexBuffer>>& Reference to the vector of vertex buffers.
         */
        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

        /**
         * @brief Get the index buffer.
         * @return const std::shared_ptr<IndexBuffer>& Reference to the shared pointer of the index buffer.
         */
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID; /**< The OpenGL renderer ID for this vertex array object. */
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers; /**< Vector of vertex buffers associated with this vertex array. */
        std::shared_ptr<IndexBuffer> m_IndexBuffer; /**< The index buffer associated with this vertex array. */
    };
}