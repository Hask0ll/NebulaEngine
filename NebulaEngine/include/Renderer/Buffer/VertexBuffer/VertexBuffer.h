#pragma once

#include "Renderer/Buffer/Layout/BufferLayout.h"

namespace Nebula
{
	class VertexBuffer : public BufferLayout
	{
	public:

		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);

		[[nodiscard]] virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
	};
}