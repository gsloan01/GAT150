#pragma once
#include <vector>
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Core/InputSystem.h"
#include "Core/Timer.h"

namespace nc
{
	class System;

	class Engine
	{
	public:
		bool Startup();
		void Shutdown();

		void Update();
		nc::FrameTimer& GetTimer() { return m_timer; };
		//template<typename T>
		//T* GetSystem();

		template<typename T>
		T* GetSystem()
		{
			T* result = nullptr;
			for (auto system : Engine::m_systems)
			{
				result = dynamic_cast<T*>(system);
				if (result) break;
			}
			return result;
		}

	protected:
		std::vector<System*> m_systems;
		nc::FrameTimer m_timer;
	};

	
}