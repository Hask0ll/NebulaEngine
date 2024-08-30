#include "Renderer/Manager/RendererManager.h"

#include <complex>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Core/Application.h"
#include "Renderer/Render/Shader/Shader.h"
#include "Renderer/Command/RenderCommand.h"

namespace Nebula
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		const float screenWidth = Application::Get().GetWindow()->GetWidth();
		const float screenHeight = Application::Get().GetWindow()->GetHeight();

		// Orthographic projection matrix
		glm::mat4 projectionMatrix = glm::ortho(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 tmp = projectionMatrix * viewMatrix * transform;
		shader->Bind();
		shader->UploadUniformMat4("u_Transform", tmp);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}