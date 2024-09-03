#include "Core/Application.h"

#include "Events/ApplicationEvent.h"
#include "Logger/Log.h"
#include "Window/Window.h"

namespace Nebula
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
		Log::Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
	}

	void Application::Run()
	{
		Log::Init();

		NB_CORE_TRACE("Nebula Engine is Running !");
		NB_CORE_TRACE("Initialyse Log.");
		NB_CLIENT_INFO("Hello !");

		WindowResizeEvent e(1280, 720);

		while(true);
	}
}
