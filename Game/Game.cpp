#include "Nebula.h"
#include "Logger/Log.h"

class ExampleLayer : public Nebula::Layer
{
	public:
	ExampleLayer()
		: Layer("Example")
	{
		m_VertexArray.reset(Nebula::VertexArray::Create());

		float vertices[3 * 7] = {
			 0.0f,  0.5f, 1.0f,0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,0.0f, 1.0f
		};

		std::shared_ptr<Nebula::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Nebula::VertexBuffer::Create(vertices, sizeof(vertices)));
		Nebula::BufferLayout layout = {
			{ Nebula::ShaderDataType::Float2,  "aPosition" },
			{ Nebula::ShaderDataType::Float3,  "aColor" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Nebula::IndexBuffer> indexBuffer;
		indexBuffer.reset(Nebula::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Nebula::VertexArray::Create());	

		float vertices2[3 * 4] = {
			0.0f,  0.5f,	1.0f,
			0.0f, 0.0f,	0.0f,
			0.5f, 0.0f,	0.0f,
			0.5f, 0.5f,		0.0f
		};

		std::shared_ptr<Nebula::VertexBuffer> squareVB;
		squareVB.reset(Nebula::VertexBuffer::Create(vertices2, sizeof(vertices2)));


		squareVB->SetLayout({
			{Nebula::ShaderDataType::Float3,  "aPosition" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareI[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Nebula::IndexBuffer> squareIB;
		squareIB.reset(Nebula::IndexBuffer::Create(squareI, sizeof(squareI)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vsSrc2 = R"(#version 330 core
		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec4 aColor;

		out vec3 vPos;
		out vec4 vColor;

		void main()
		{
			vPos = aPos;
			vColor = aColor;
			gl_Position = vec4(aPos, 1.0); 
		})";

		std::string fsSrc2 = R"(#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 vPos;

		void main()
		{
			color = vec4(0.2, 0.4, 0.1, 1.0);
		})";

		const char* vsSrc = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aColor;\n"
			"out vec3 ourColor;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos, 1.0);\n"
			"   ourColor = aColor;\n"
			"}\0";

		const char* fsSrc = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 ourColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(ourColor, 1.0f);\n"
			"}\n\0";

		BlueShader.reset(new Nebula::Shader(vsSrc2, fsSrc2));
	}

	void OnUpdate(Nebula::TimeStep ts) override
	{
		Nebula::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Nebula::RenderCommand::Clear();

		Nebula::RendererManager::BeginScene();

		Nebula::RendererManager::Submit(m_SquareVA, BlueShader);

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
private:
	std::shared_ptr<Nebula::Shader> m_Shader;
	std::shared_ptr<Nebula::VertexArray> m_VertexArray;

	std::shared_ptr<Nebula::Shader> BlueShader;
	std::shared_ptr<Nebula::VertexArray> m_SquareVA;
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
