#include "Renderer/VertexArray/VertexArray.h"

#include "Platforms/OpenGl/VertexArray/OpenGLVertexArray.h"
#include "Renderer/Manager/RendererManager.h"
#include "Renderer/Api/RendererApi.h"

namespace Nebula
{
	VertexArray* VertexArray::Create()
	{
		switch (RendererManager::GetAPI())
		{
			case RendererApi::API::None:		return nullptr;
			case RendererApi::API::OpenGl:		return new OpenGLVertexArray();
		}

		return nullptr;
	}

}