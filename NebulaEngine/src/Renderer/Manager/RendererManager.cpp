#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/Manager/RendererManager.h"
#include "Core/Application.h"
#include "Renderer/Command/RendererCommand.h"
#include "Renderer/Render/Shader/Shader.h"
#include "Renderer/VertexArray/VertexArray.h"

namespace Nebula
{
	void RendererManager::BeginScene()
	{

	}

	void RendererManager::EndScene()
	{

	}

	void RendererManager::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		const unsigned int screenWidth = Application::Get().GetWindow().GetWidth();
		const unsigned int screenHeight = Application::Get().GetWindow().GetHeight();

		// Orthographic projection matrix
        glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 tmp = projectionMatrix * viewMatrix * transform;
		shader->Bind();
		shader->UploadUniformMat4("u_Transform", tmp);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
