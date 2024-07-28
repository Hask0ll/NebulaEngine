#pragma once
#include <cstdint>

#include "Renderer/Buffer/IndexBuffer.h"

namespace Nebula
{
	class OpenGlIndexBuffer : public IndexBuffer
	{
	public:
		OpenGlIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGlIndexBuffer() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		[[nodiscard]] virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_Count;
		uint32_t m_RendererID;
	};
}