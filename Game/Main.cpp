#include "pch.h"
#include "Engine.h"
#include "Graphics/Texture.h"
#include "Math/Vector2.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Core/Factory.h"
#include "Objects/ObjectFactory.h"
#include <SDL_image.h>
#include "Objects/Scene.h"

nc::Engine engine;
nc::GameObject player;
nc::Scene scene;


int main(int, char**)
{
	engine.Startup();
	scene.Create(&engine);


	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);

	scene.Read(document);

	/*for (size_t i=0; i<10; i++)
	{
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoExplosion");
		gameObject->m_transform.position = nc::Vector2{ nc::random(0, 800), nc::random(0, 800) };
		gameObject->m_transform.angle = nc::random(0, 360);
		scene.AddGameObject(gameObject);
	}*/
	
	SDL_Event event;
	bool quit = false;
	while (!quit) 
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Update();
		scene.Update();

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::HELD)
		{
			quit = true;
		}

		engine.GetSystem<nc::Renderer>()->BeginFrame(); // BEGIN FRAME

		scene.Draw();
		
		engine.GetSystem<nc::Renderer>()->EndFrame(); //END FRAME
	}
	engine.Shutdown();

	return 0;
	/*std::string str;
	nc::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	nc::json::Get(document, "boolean", b);
	std::cout << b << std::endl;

	int i1;
	nc::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	nc::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	nc::json::Get(document, "float", f);
	std::cout << f << std::endl;

	nc::Vector2 v2;
	nc::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	nc::Color color;
	nc::json::Get(document, "color", color);
	std::cout << color << std::endl;*/
}

