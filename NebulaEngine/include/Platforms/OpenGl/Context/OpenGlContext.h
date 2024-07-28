#pragma once
#include "Renderer/Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Nebula
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}