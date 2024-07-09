#include "Core/Core.h"
#include "../Logger/Log.h"

namespace Nebula
{
	class NEBULA Engine
	{
	public:
		Engine();
		virtual ~Engine();


		/*
		 * Brief: Run the application
		 *
		 *	balbdkjafbe
		 * @param void
		 */
		virtual void Run();
	};

	Engine* CreateEngine();
}