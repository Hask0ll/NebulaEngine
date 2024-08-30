#pragma once

#include <glm/fwd.hpp>

namespace KDME
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

	private:
		//struct SceneData
		//{
		//	glm::mat4  ViewProjectionMatrix;
		//};

		//static std::unique_ptr<SceneData> s_SceneData;
	};
}