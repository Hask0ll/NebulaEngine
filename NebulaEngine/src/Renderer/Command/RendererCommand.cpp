#include "Renderer/Command/RendererCommand.h"

#include "Platforms/OpenGl/Renderer/OpenGLRendererApi.h"
#include "Renderer/Api/RendererApi.h"

namespace Nebula
{
	RendererApi* RenderCommand::s_RendererApi = new OpenGLRendererApi();
}
