#include "platform/OpenGl/Buffer/OpenGlVertexBuffer.h"

#include <glad/glad.h>

#include "Renderer/Buffer/VertexBuffer.h"

namespace Nebula
{
	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGlVertexBuffer::~OpenGlVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGlVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGlVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}