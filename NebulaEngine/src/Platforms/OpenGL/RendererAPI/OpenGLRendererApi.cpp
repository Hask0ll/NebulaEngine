#include <memory>

#include "Platforms/OpenGL/Renderer/OpenGLRendererApi.h"
#include "Renderer/VertexArray/VertexArray.h"

#include <glad/glad.h>
#include <glm/fwd.hpp>

namespace Nebula
{
	void OpenGLRendererApi::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererApi::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererApi::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}
