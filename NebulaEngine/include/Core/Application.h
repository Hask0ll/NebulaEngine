#include "Core/Core.h"

namespace Nebula
{
	class NEBULA Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
	};

	Application* CreateApplication();
}