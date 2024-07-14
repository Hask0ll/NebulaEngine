#include "Core/Core.h"

namespace Nebula
{
	class NEBULA Application
	{
	public:
		Application();
		virtual ~Application();

		/*
		 * Brief: Run the application
		 *
		 * @param char** : Hello
		 */
		virtual void Run();
	};

	Application* CreateApplication();
}