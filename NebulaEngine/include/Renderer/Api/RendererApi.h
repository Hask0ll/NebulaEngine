#pragma once

#include "Renderer/VertexArray/VertexArray.h"

#include <cstdint>

namespace Nebula
{
	class NEBULA RendererApi
	{
	public:
		enum class API
		{
			None = 0, OpenGl = 1
		};
	public:
		virtual ~RendererApi() = default;

		//virtual void Init() = 0;
		//virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
		//virtual void DrawLines(const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount) = 0;

		//virtual void SetLineWidth(float width) = 0;

		static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}