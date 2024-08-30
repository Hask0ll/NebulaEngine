#include "Renderer/Command/RenderCommand.h"

#include "Platforms/OpenGl/Api/OpenGLRendererApi.h"

namespace Nebula
{
	RendererApi* RenderCommand::s_RendererApi = new OpenGLRendererApi();
}