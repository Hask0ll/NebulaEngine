#pragma once
#include "Renderer/Api/RendererApi.h"
#include "Renderer/Render/Shader/Shader.h"
#include <glm/glm.hpp>

#include "Renderer/Camera/OrthographicCamera.h"

namespace Nebula
{
	class NEBULA RendererManager
	{
	public:
		static void BeginScene(OrthographicCamera& camera);

		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererApi::API GetAPI() { return RendererApi::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4  ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
}
