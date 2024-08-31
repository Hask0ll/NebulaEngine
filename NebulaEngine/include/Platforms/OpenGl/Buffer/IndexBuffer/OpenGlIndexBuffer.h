#pragma once
#include <cstdint>

#include "Renderer/Buffer/IndexBuffer/IndexBuffer.h"

namespace Nebula
{
	/**
	 * \brief OpenGL implementation of an Index Buffer.
	 *
	 * The OpenGLIndexBuffer class manages an OpenGL index buffer object (IBO),
	 * which is used to specify the order in which vertices are rendered.
	 */
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		/**
		 * \brief Constructs an OpenGLIndexBuffer with the given indices.
		 * \param indices A pointer to an array of indices.
		 * \param count The number of indices in the array.
		 */
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		/**
		 * \brief Destructor that cleans up the OpenGL index buffer.
		 */
		virtual ~OpenGLIndexBuffer();

		/**
		 * \brief Binds the index buffer to the current OpenGL context.
		 */
		virtual void Bind() const override;

		/**
		 * \brief Unbinds the index buffer from the current OpenGL context.
		 */
		virtual void UnBind() const override;

		/**
		 * \brief Gets the number of indices stored in the index buffer.
		 * \return The number of indices in the buffer.
		 */
		[[nodiscard]] virtual uint32_t GetCount() const override { return m_Count; }

	private:
		/** \brief The number of indices in the buffer. */
		uint32_t m_Count;

		/** \brief The OpenGL renderer ID for the index buffer object (IBO). */
		uint32_t m_RendererID;
	};
}
