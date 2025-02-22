#include "Platforms/OpenGL/Buffer/VertexBuffer/OpenGLVertexBuffer.h"
#include <glad/glad.h>

#include "Logger/Log.h"

namespace Nebula
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		if (!vertices) {
			NB_CORE_ERROR("Vertex buffer creation failed: vertices pointer is null!");
			return;
		}

		if (size == 0) {
			NB_CORE_ERROR("Vertex buffer creation failed: size is 0!");
			return;
		}

		NB_CORE_TRACE("Creating OpenGL vertex buffer...");
		NB_CORE_TRACE("Buffer size: {0}", size);

		glCreateBuffers(1, &m_RendererID);
		if (m_RendererID == 0) {
			NB_CORE_ERROR("Failed to create OpenGL buffer!");
			return;
		}
		NB_CORE_TRACE("Buffer ID: {0}", m_RendererID);

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			NB_CORE_ERROR("Failed to bind buffer! GL Error: {0}", error);
			return;
		}

		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		error = glGetError();
		if (error != GL_NO_ERROR) {
			NB_CORE_ERROR("Failed to buffer data! GL Error: {0}", error);
			return;
		}

		NB_CORE_TRACE("Successfully created vertex buffer");
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}
