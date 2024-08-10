#pragma once

#include "Platforms/OpenGL/Context/OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Logger/Log.h"

namespace Nebula
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status)
		{
			NB_CORE_ERROR("Failed to initialize Glad!");
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}