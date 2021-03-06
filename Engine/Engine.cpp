#include "pch.h"
#include "Engine.h"
#include <time.h>
namespace nc 
{

bool Engine::Startup()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
	Engine::m_systems.push_back(new Renderer);
	Engine::m_systems.push_back(new InputSystem);
	Engine::m_systems.push_back(new ResourceManager);
	Engine::m_systems.push_back(new PhysicsSystem);
	Engine::m_systems.push_back(new AudioSystem);
	for (auto system : m_systems)
	{
		system->Startup();
	}
	GetSystem<Renderer>()->Create("pog", 800, 500);
	return true;
}

void Engine::Shutdown()
{
	for (auto system : m_systems)
	{
		system->Shutdown();
		delete system;
	}
	m_systems.clear();
	SDL_Quit();
}

void Engine::Update()
{
	m_timer.Tick();
	for (auto system : m_systems)
	{
		system->Update();
	}
}

}