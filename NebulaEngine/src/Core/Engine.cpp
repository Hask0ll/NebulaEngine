#include "Core/Engine.h"

namespace Nebula
{
	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
		Log::Shutdown();
	}

	void Engine::Run()
	{
		Log::Init();

		NB_CORE_INFO("Nebula Engine is Running !");
		while(true);
	}
}
