#pragma once
#include "Renderer/Api/RendererApi.h"
#include "Renderer/Render/Shader/Shader.h"
#include <glm/glm.hpp>

namespace Nebula
{
	class NEBULA RendererManager
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererApi::API GetAPI() { return RendererApi::GetAPI(); }
	};
}