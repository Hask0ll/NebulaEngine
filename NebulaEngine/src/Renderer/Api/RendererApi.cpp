#include "Renderer/Api/RendererApi.h"

#include "Platforms/OpenGL/Renderer/OpenGLRendererApi.h"

namespace Nebula
{
	RendererApi::API RendererApi::s_API = RendererApi::API::OpenGl;
}