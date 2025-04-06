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
#include <glm/ext/matrix_transform.hpp>

#include "Renderer/Command/RendererCommand.h"
#include "Renderer/Manager/RendererManager.h"

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

		// Ajoutez ces logs
		NB_CORE_TRACE("Application constructor start");

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

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

		float vertices2[4 * 3] = {
			-0.5f,  0.5f, 0.0f,    // top left
			-0.5f, -0.5f, 0.0f,    // bottom left
			 0.5f, -0.5f, 0.0f,    // bottom right
			 0.5f,  0.5f, 0.0f     // top right
		};

		NB_CORE_TRACE("Creating square vertex buffer...");
		std::shared_ptr<Nebula::VertexBuffer> squareVB;
		squareVB.reset(Nebula::VertexBuffer::Create(vertices2, sizeof(vertices2)));

		if (!squareVB) {
			NB_CORE_ERROR("Failed to create square vertex buffer!");
			return;
		}

		squareVB->SetLayout({
			{Nebula::ShaderDataType::Float3, "aPosition"}
		});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareI[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Nebula::IndexBuffer> squareIB;
		squareIB.reset(Nebula::IndexBuffer::Create(squareI, sizeof(squareI)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vsSrc2 = R"(
			#version 330 core
			layout(location = 0) in vec3 aPos;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
			})";

		std::string fsSrc2 = R"(#version 330 core
	    layout(location = 0) out vec4 color;

	    uniform vec4 u_Color;  // Ajoutez ceci

	    void main()
	    {
	        color = u_Color;  // Utilisez la couleur uniforme
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
		m_BlueShader.reset(new Nebula::Shader(vsSrc2, fsSrc2));
		m_Shader.reset(new Nebula::Shader(vsSrc, fsSrc));
		NB_CORE_TRACE("Application constructor end");
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

	void Application::AddSquare(const Square& square)
	{
		m_Squares.push_back(square);
	}

	void Application::HandleCameraInput(TimeStep ts)
	{
		glm::vec3 cameraPosition = m_Camera.GetPosition();

		float cameraSpeed = 2.0f * ts;

		if (Nebula::Input::IsKeyPressed(GLFW_KEY_W) || Nebula::Input::IsKeyPressed(GLFW_KEY_Z))
		{
			cameraPosition.y += cameraSpeed;
		}
		if (Nebula::Input::IsKeyPressed(GLFW_KEY_S))
		{
			cameraPosition.y -= cameraSpeed;
		}
		if (Nebula::Input::IsKeyPressed(GLFW_KEY_A) || Nebula::Input::IsKeyPressed(GLFW_KEY_Q))
		{
			cameraPosition.x -= cameraSpeed;
		}
		if (Nebula::Input::IsKeyPressed(GLFW_KEY_D))
		{
			cameraPosition.x += cameraSpeed;
		}

		m_Camera.SetPosition(cameraPosition);
	}

	void Application::Run()
	{
		NB_CORE_TRACE("Nebula Engine is Running !");
		NB_CORE_TRACE("Initialize Log.");
		NB_CORE_TRACE("Application::Run started");

		WindowResizeEvent e(1280, 720);

		while(m_Running)
		{
			try {
				float time = (float)glfwGetTime();
				TimeStep timestep = time - m_LastFrameTime;
				m_LastFrameTime = time;

				RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
				RenderCommand::Clear();

				HandleCameraInput(timestep);

				for (Layer* layer : m_LayerStack) {
					NB_CORE_TRACE("Updating layer: {0}", layer->GetName());
					layer->OnUpdate(timestep);
				}

				Nebula::ImGuiLayer::Begin();

				RendererManager::BeginScene(m_Camera);

				if (m_BlueShader && m_SquareVA)
				{
					// Vérifiez que l'index buffer est présent
					auto indexBuffer = m_SquareVA->GetIndexBuffer();
					if (!indexBuffer) {
						NB_CORE_ERROR("No index buffer!");
					} else {
						NB_CORE_TRACE("Index buffer count: {0}", indexBuffer->GetCount());
					}

					for(const auto& square : m_Squares)
					{
						glm::mat4 transform = glm::translate(glm::mat4(1.0f), square.Position);
						m_BlueShader->UploadUniformMat4("u_Transform", transform);
						m_BlueShader->UploadUniformFloat4("u_Color", square.Color.r, square.Color.g, square.Color.b, 1.0f); // Assuming alpha is 1.0f
						RendererManager::Submit(m_SquareVA, m_BlueShader, transform);
					}

					// Check for OpenGL errors
					GLenum error = glGetError();
					if (error != GL_NO_ERROR) {
						NB_CORE_ERROR("OpenGL Error: {0}", error);
					}
				} else {
					NB_CORE_ERROR("Shader or VAO is null!");
				}

				RendererManager::EndScene();

				for (Layer* layer : m_LayerStack) {
					NB_CORE_TRACE("ImGui render for layer: {0}", layer->GetName());
					layer->OnImGuiRender();
				}

				Nebula::ImGuiLayer::End();

				m_Window->OnUpdate();

			} catch (const std::exception& exception) {
				NB_CORE_ERROR("Exception in main loop: {0}", exception.what());
				break;
			}
		}

		NB_CORE_TRACE("Application::Run ended");
	}
}
