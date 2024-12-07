#pragma once

#include <memory>

#include "Renderer/Api/RendererApi.h"

namespace Nebula
{
	class NEBULA OpenGLRendererApi : public RendererApi
	{
	public:
		//virtual void Init() override;
		//virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
		//virtual void DrawLines(const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount) override;

		//virtual void SetLineWidth(float width) override;
	};
}