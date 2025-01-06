#pragma once

#include "Core/Core.h"
#include "Renderer/Buffer/Layout/BufferLayout.h"

namespace Nebula
{
	class NEBULA IndexBuffer : public BufferLayout
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);

		virtual uint32_t GetCount() const = 0;
	};
}