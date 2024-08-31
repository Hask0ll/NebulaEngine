#pragma once

#include <cstdint>

#include "Renderer/Buffer/VertexBuffer/VertexBuffer.h"
#include "Renderer/Buffer/Layout/BufferLayout.h"

namespace Nebula
{
	/**
	 * \brief OpenGL implementation of a Vertex Buffer.
	 *
	 * The OpenGLVertexBuffer class represents an OpenGL vertex buffer object (VBO),
	 * which stores vertex data used for rendering. This class provides methods to bind,
	 * unbind the buffer, and set or get its layout.
	 */
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		/**
		 * \brief Constructs an OpenGLVertexBuffer with the given vertex data.
		 * \param vertices A pointer to an array of vertex data.
		 * \param size The size of the vertex data array in bytes.
		 */
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		/**
		 * \brief Destructor that cleans up the OpenGL vertex buffer.
		 */
		virtual ~OpenGLVertexBuffer();

		/**
		 * \brief Binds the vertex buffer to the current OpenGL context.
		 *
		 * This method makes the vertex buffer the active buffer for rendering operations.
		 */
		virtual void Bind() const override;

		/**
		 * \brief Unbinds the vertex buffer from the current OpenGL context.
		 *
		 * This method deactivates the vertex buffer so that it is no longer used for rendering.
		 */
		virtual void UnBind() const override;

		/**
		 * \brief Gets the buffer layout of the vertex buffer.
		 * \return A reference to the buffer layout of the vertex buffer.
		 */
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		/**
		 * \brief Sets the buffer layout of the vertex buffer.
		 * \param layout A reference to the new buffer layout to set.
		 */
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		/** \brief The OpenGL renderer ID for the vertex buffer object (VBO). */
		uint32_t m_RendererID;

		/** \brief The layout of the vertex buffer, defining the structure of vertex data. */
		BufferLayout m_Layout;
	};
}
