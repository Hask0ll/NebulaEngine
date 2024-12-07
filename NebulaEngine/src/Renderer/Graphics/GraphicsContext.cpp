#include "Renderer/Graphics/GraphicsContext.h"

#include <memory>

#include "Platforms/OpenGL/Context/OpenGLContext.h"
#include "Renderer/Manager/RendererManager.h"
#include "Renderer/Api/RendererApi.h"

namespace Nebula
{
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (RendererManager::GetAPI())
		{
			case RendererApi::API::None:    NB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererApi::API::OpenGl:  return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		return nullptr;
	}
}
