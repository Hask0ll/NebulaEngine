#pragma once

#include <cstdint>

#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/BufferLayout.h"

namespace Nebula
{
	class OpenGlVertexBuffer : public VertexBuffer
	{
	public:
		OpenGlVertexBuffer(float* vertices, uint32_t size);

		virtual ~OpenGlVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}