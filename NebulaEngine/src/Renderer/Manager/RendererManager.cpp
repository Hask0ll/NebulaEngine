#include "Renderer/Manager/RendererManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include "Core/Application.h"
#include "Logger/Log.h"
#include "Renderer/Command/RendererCommand.h"
#include "Renderer/Render/Shader/Shader.h"
#include "Renderer/VertexArray/VertexArray.h"
#include "Renderer/Camera/OrthographicCamera.h"

namespace Nebula
{
	RendererManager::SceneData* RendererManager::m_SceneData = new RendererManager::SceneData;

	void RendererManager::BeginScene(::Nebula::OrthographicCamera &camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void RendererManager::EndScene()
	{

	}

	void RendererManager::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
