#include "Nebula.h"

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
