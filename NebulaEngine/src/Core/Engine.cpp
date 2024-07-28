#include "Core/Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Logger/Log.h"

namespace Nebula
{
	Application::Application()
	{
	}

	Application::~Application()
	{
		Log::Shutdown();
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
