#include "Nebula.h"

class Game : public Nebula::Engine
{
public:
	Game()
	{
	}

	~Game()
	{
	}
};

Nebula::Engine* Nebula::CreateEngine()
{
	return new Game();
}
