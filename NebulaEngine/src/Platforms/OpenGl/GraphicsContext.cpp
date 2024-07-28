#include "Renderer/Graphics/GraphicsContext.h"

#include "platform/OpenGl/OpenGlContext.h"
#include "Renderer/Render/Render.h"

namespace KDME
{
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
		/*switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}*/

		return nullptr;
	}
}