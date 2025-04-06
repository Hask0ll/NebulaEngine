#pragma once

#include <memory>

#include "Core/Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Layer/Layer.h"
#include "Layer/LayerStack.h"
#include "Renderer/Buffer/IndexBuffer/IndexBuffer.h"
#include "Renderer/Buffer/VertexBuffer/VertexBuffer.h"
#include "Renderer/Render/Shader/Shader.h"
#include "Window/Window.h"
#include "Renderer/Camera/OrthographicCamera.h"
#include "ImGui/ImGuiLayer.h"

/**
 * @file Application.h
 * @author Haskoll
 * @date 2024
 * @brief Header file for the Application class.
 */

namespace Nebula
{
	class VertexArray;
	/**
	 * \brief Application class
	 *
	 * The main class responsible for managing the application's lifecycle, handling events,
	 * and managing the main window. 
	 */
	class NEBULA Application
	{
	public:
		/**
		 * \brief Construct a new Application object
		 */
		Application();

		/**
		 * \brief Destroy the Application object
		 */
		virtual ~Application();

		/**
		 * \brief Run the application.
		 *
		 * This is the main loop of the application where events are processed and
		 * the application's state is updated.
		 */
		virtual void Run();

		/**
		 * \brief Handle an event.
		 *
		 * This function is called whenever an event occurs in the application.
		 * The event is passed by reference and handled according to its type.
		 *
		 * \param e The event to be handled.
		 */
		void OnEvent(Event& e);

		/**
		 * \brief Handle window close event.
		 *
		 * This function is called when a window close event is triggered.
		 *
		 * \param e The window close event.
		 * \return true if the event was handled, false otherwise.
		 */
		bool OnWindowClose(WindowCloseEvent& e);

		/**
		 * \brief Handle window resize event.
		 *
		 * This function is called when a window resize event occurs.
		 *
		 * \param e The window resize event.
		 * \return true if the event was handled, false otherwise.
		 */
		bool OnWindowResize(WindowResizeEvent& e);

		/**
		 * \brief Get the application instance.
		 *
		 * This is the main entry point for accessing the application instance.
		 *
		 * \return Reference to the application instance.
		 */
		static Application& Get() { return *s_Instance; }

		/**
		 * \brief Get the window instance.
		 *
		 * This function returns a reference to the application's main window.
		 *
		 * \return Reference to the window instance.
		 */
		Window& GetWindow() { return *m_Window; }

		/**
		 * \brief Push a layer to the layer stack.
		 *
		 * Layers are updated in the order they are pushed.
		 *
		 * \param layer The layer to be pushed onto the stack.
		 */
		 void PushLayer(Layer* layer);

		 /**
		  * \brief Push an overlay to the layer stack.
		  *
		  * An overlay is a special type of layer that is always updated after all the other layers.
		  *
		  * \param overlay The overlay to be pushed onto the stack.
		  */
		  void PushOverlay(Layer* overlay);

		  /**
		   * \brief Start all game objects.
		   *
		   * This function calls the Start() method of all game objects in the hierarchy starting from the root.
		   *
		   * \param root The root game object.
		   */
		   //static void StartGameObjects(NEBULA::ECS::GameObject* root);

		   /**
			* \brief Update all game objects.
			*
			* This function calls the Update() method of all game objects in the hierarchy starting from the root.
			*
			* \param root The root game object.
			* \param deltaTime Time elapsed between two frames.
			*/
			//static void UpdateGameObjects(NEBULA::ECS::GameObject* root, float deltaTime);

			/**
			 * \brief Draw all game objects.
			 *
			 * This function calls the Draw() method of all game objects in the hierarchy starting from the root.
			 *
			 * \param root The root game object.
			 */
			 //static void DrawGameObjects(NEBULA::ECS::GameObject* root);

		 /**
		  * \brief Stop the application.
		  *
		  * This function stops the application's main loop.
		  */
		void Stop() { m_Running = false; }

		struct Square {
			glm::vec3 Position;
			glm::vec3 Color;
			// Vous pouvez ajouter d'autres propriétés comme la taille, rotation, etc.
		};

		void AddSquare(const Square& square);


	private:

		void HandleCameraInput(TimeStep ts);

		std::vector<Square> m_Squares;
		std::shared_ptr<Window> m_Window; /**< The main window of the application. */
		bool m_Running = true;            /**< Flag indicating whether the application is running. */
		inline static Application* s_Instance;          /**< Pointer to the application instance (singleton pattern). */
		LayerStack m_LayerStack;        /**< Stack of layers managed by the application. */
		float m_LastFrameTime = 0.0f;     /**< Time of the last frame, used for time management. */

		OrthographicCamera m_Camera; /**< The main camera of the application. */

		ImGuiLayer *m_ImGuiLayer;

		std::shared_ptr<Nebula::Shader> m_Shader;
		std::shared_ptr<Nebula::VertexArray> m_VertexArray;

		std::shared_ptr<Nebula::Shader> m_BlueShader;
		std::shared_ptr<Nebula::VertexArray> m_SquareVA;
	};

	/**
	 * \brief Create the application.
	 *
	 * This function is used to create an instance of the application.
	 * Typically implemented by the client.
	 *
	 * \return Pointer to the created application instance.
	 */
	Application* CreateApplication();
}
