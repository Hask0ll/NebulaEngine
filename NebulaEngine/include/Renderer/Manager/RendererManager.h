#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include "Renderer/Manager/RendererAPI.h"
#include "Renderer/Render/Shader/Shader.h"

namespace Nebula
{
	class NEBULA_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}