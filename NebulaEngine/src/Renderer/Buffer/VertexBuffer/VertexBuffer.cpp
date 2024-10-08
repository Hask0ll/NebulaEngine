#include "Renderer/Buffer/VertexBuffer/VertexBuffer.h"
#include "Renderer/Api/RendererAPI.h"
#include "Platforms/OpenGl/Buffer/VertexBuffer/OpenGlVertexBuffer.h"
#include "Renderer/Manager/RendererManager.h"

namespace Nebula
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererManager::GetAPI())
		{
		case RendererApi::API::None:		return nullptr;
		case RendererApi::API::OpenGl:	return new OpenGLVertexBuffer(vertices, size);
		}

		return nullptr;
	}

}