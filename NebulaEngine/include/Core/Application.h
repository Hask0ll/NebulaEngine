#pragma once

#include "Core/Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Window/Window.h"

namespace Nebula
{
	/**
	 * \brief 
	 */
	class NEBULA Application
	{
	public:
		Application();
		virtual ~Application();

		/*
		 * Brief: Run the application
		 *
		 */
		virtual void Run();

		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);


		/**
		 * \brief
		 * Return the application instance, main entry point for getting the application instance
		 * \return
		 * s_instance
		 */
		Application& Get() { return *s_Instance; }

		/**
		 * \brief
		 * Return instance of the window
		 * \return
		 * window instance
		 */
		Window& GetWindow() { return *m_Window; }


		/**
		 * \brief
		 * Push a layer to the layer stack
		 * Be aware that the layers are updated in the order they are pushed
		 * \param layer 
		 */
		//void PushLayer(Layer* layer);


		/**
		 * \brief
		 * Push an overlay to the layer stack
		 * An overlay is a layer that is updated after all the layers
		 * \param overlay 
		 */
		//void PushOverlay(Layer* overlay);

		/**
		 * \brief
		 * Call the Start() function of game objects
		 * \param root The root game object
		 */
		//static void StartGameObjects(NEBULA::ECS::GameObject* root);

		/**
		 * \brief
		 * Call the Update() function of game objects
		 * \param root The root game object
		 * \param deltaTime Time elapsed between two frames
		 */
		//static void UpdateGameObjects(NEBULA::ECS::GameObject* root, float deltaTime);

		/**
		 * \brief Call the Draw() function of game objects
		 * \param root The root game object
		 */
		//static void DrawGameObjects(NEBULA::ECS::GameObject* root);

		/**
		 * \brief Stop the application
		 */
		void Stop() { m_Running = false; }

	private:

		std::shared_ptr<Window> m_Window;
		bool m_Running = true;
		Application* s_Instance;
		//LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	};

	Application* CreateApplication();
}
