#include "Core/Application.h"

#include "Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"
#include "Inputs/InputManager.h"
#include "Logger/Log.h"
#include "TimeStep/TimeStep.h"
#include "Window/Window.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Nebula
{
	Application::Application() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		if (s_Instance)
			NB_CORE_ERROR("Instance of Application already exists !");
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback([this]<typename T0>(T0 && PH1) { OnEvent(std::forward<T0>(PH1)); });
		s_Instance = this;
		m_LastFrameTime = (float)glfwGetTime();
	}

	Application::~Application()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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
		NB_CORE_TRACE("Initialize Log.");
		NB_CLIENT_INFO("Hello !");

		WindowResizeEvent e(1280, 720);

		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window->NativeWindow());

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsClassic();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		while(m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_LastFrameTime;

			m_LastFrameTime = time;

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("HELLO");
			ImGui::Text("Coucou");
			ImGui::End();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			m_Window->OnUpdate();
		}
		glfwDestroyWindow(window);

		glfwTerminate();
	}
}
