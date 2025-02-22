#pragma once

#include <cstdint>

#include "Core/Core.h"

namespace Nebula
{
	class NEBULA Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);
	};
}