#include "Core/Application.h"

#include "Events/ApplicationEvent.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Inputs/InputManager.h"
#include "Logger/Log.h"
#include "Renderer/Buffer/IndexBuffer/IndexBuffer.h"
#include "Renderer/Buffer/VertexBuffer/VertexBuffer.h"
#include "Renderer/Render/Shader/Shader.h"
#include "Window/Window.h"
#include "TimeStep/TimeStep.h"

namespace Nebula
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		s_Instance = this;
	}

	Application::~Application()
	{
		Log::Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}

	void Application::Run()
	{

		NB_CORE_TRACE("Nebula Engine is Running !");
		NB_CORE_TRACE("Initialyse Log.");
		NB_CLIENT_INFO("Hello !");

		WindowResizeEvent e(1280, 720);

		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window->NativeWindow());

		while(m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_Window->OnUpdate();
		}
		glfwDestroyWindow(window);

		glfwTerminate();
	}
}
