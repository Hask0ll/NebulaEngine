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
		Nebula::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Nebula::RenderCommand::Clear();

		Nebula::RendererManager::BeginScene();

		Nebula::RendererManager::EndScene();
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
		PushLayer(new ExampleLayer());
	}

	~Game()
	{
	}
};

Nebula::Application* Nebula::CreateApplication()
{
	return new Game();
}
