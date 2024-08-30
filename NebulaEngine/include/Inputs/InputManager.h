#pragma once

#include <utility>

#include "Core/Core.h"

namespace Nebula
{
	class NEBULA Input
	{
	public:
		[[ nodiscard]] static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		[[ nodiscard]] static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		[[ nodiscard]] static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		[[ nodiscard]] static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		[[ nodiscard]] static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* s_Instance;
	};
}