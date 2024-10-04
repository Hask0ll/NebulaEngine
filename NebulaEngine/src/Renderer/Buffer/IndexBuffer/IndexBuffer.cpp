#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Buffer/IndexBuffer/IndexBuffer.h"

#include "Platforms/OpenGl/Buffer/IndexBuffer/OpenGlIndexBuffer.h"
#include "Renderer/Manager/RendererManager.h"
#include "Renderer/Api/RendererAPI.h"

namespace Nebula
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererApi::API::None:		return nullptr;
		case RendererApi::API::OpenGl:		return new OpenGLIndexBuffer(indices, size);
		}
		return nullptr;
	}
}