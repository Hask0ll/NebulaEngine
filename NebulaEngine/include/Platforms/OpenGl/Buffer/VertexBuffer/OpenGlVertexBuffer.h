#pragma once

#include <cstdint>

#include "Renderer/Buffer/VertexBuffer/VertexBuffer.h"
#include "Renderer/Buffer/Layout/BufferLayout.h"

namespace Nebula
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const;
		virtual void UnBind() const;

		virtual const BufferLayout& GetLayout() const { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}