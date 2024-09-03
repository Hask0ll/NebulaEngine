#include "Core/Application.h"
#include "Platforms/Windows/WindowsInput.h"

#include <GLFW/glfw3.h>

namespace Nebula
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		//auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().NativeWindow());
		//auto state = glfwGetKey(window, keycode);
		//return state == GLFW_PRESS || state == GLFW_REPEAT;
		return true;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		/*auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().NativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;*/
		return true;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		/*auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().NativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };*/
		return { 0.0f, 0.0f };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}


}
