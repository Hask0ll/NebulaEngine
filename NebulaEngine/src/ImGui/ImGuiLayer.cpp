#include "ImGui/ImGuiLayer.h"
#include "Core/Application.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.inl>

#include "Logger/Log.h"

namespace Nebula
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer() = default;

	void ImGuiLayer::OnImGuiRender()
	{
		ImGui::Begin("Square Creator");

		static glm::vec3 position(0.0f);
		static glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);

		ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f);
		ImGui::ColorEdit4("Color", glm::value_ptr(color));

		if (ImGui::Button("Add Square"))
		{
			Application::Get().AddSquare({position, color});
		}

		ImGui::End();
	}

	void ImGuiLayer::OnAttach()
	{
		NB_CORE_TRACE("ImGuiLayer::OnAttach started");

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().NativeWindow());

		if (!window) {
			NB_CORE_ERROR("Window is null in ImGuiLayer::OnAttach");
			return;
		}

		// Initialiser GLFW et OpenGL pour ImGui
		if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
			NB_CORE_ERROR("Failed to initialize ImGui GLFW implementation");
			return;
		}

		if (!ImGui_ImplOpenGL3_Init("#version 330")) {
			NB_CORE_ERROR("Failed to initialize ImGui OpenGL3 implementation");
			return;
		}

		// Définir la taille initiale
		io.DisplaySize = ImVec2(
			static_cast<float>(app.GetWindow().GetWidth()),
			static_cast<float>(app.GetWindow().GetHeight())
		);

		NB_CORE_TRACE("ImGuiLayer::OnAttach completed successfully");
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(
			static_cast<float>(app.GetWindow().GetWidth()),
			static_cast<float>(app.GetWindow().GetHeight())
		);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}
