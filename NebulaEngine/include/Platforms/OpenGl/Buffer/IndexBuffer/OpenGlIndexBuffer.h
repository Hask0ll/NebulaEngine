#pragma once
#include <cstdint>

#include "Renderer/Buffer/IndexBuffer/IndexBuffer.h"

namespace Nebula
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

		[[nodiscard]] virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_Count;
		uint32_t m_RendererID;
	};
}
