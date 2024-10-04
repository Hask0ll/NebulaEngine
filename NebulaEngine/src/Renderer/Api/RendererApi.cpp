#include "Renderer/Api/RendererApi.h"

#include "Platforms/OpenGL/RendererApi/OpenGLRendererApi.h"

namespace Nebula
{
	RendererApi::API RendererApi::s_API = RendererApi::API::OpenGl;
}