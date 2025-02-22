#include "Nebula.h"
#include "Logger/Log.h"

class ExampleLayer : public Nebula::Layer
{
	public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate(Nebula::TimeStep ts) override
	{
	}

	void OnEvent(Nebula::Event& event) override
	{
		Nebula::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Nebula::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Nebula::KeyPressedEvent& event)
	{
		return false;
	}
};

class Game : public Nebula::Application
{
public:
	Game()
	{
	}

	~Game()
	{
	}
};

Nebula::Application* Nebula::CreateApplication()
{
	return new Game();
}
