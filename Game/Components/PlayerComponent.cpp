#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Core/InputSystem.h"
#include "Components/RigidBodyComponent.h"
#include "Audio/AudioComponent.h"
namespace nc
{

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	return false;
}

void nc::PlayerComponent::Destroy()
{
}

void nc::PlayerComponent::Update()
{
	auto contacts = m_owner->GetContactsWithTag("Floor");
	bool onGround = !contacts.empty();


	nc::Vector2 force{0,0};
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = -80;


		//Old Rotation Controls
		//m_owner->m_transform.angle = m_owner->m_transform.angle - 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = 80;
		//m_owner->m_transform.angle = m_owner->m_transform.angle + 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
	{
		force.y = -1200;
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		if (audioComponent)
		{
			audioComponent->Play();
		}

	}


	/*if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
	{
		force = nc::Vector2::forward * 1000;

	}*/
	//force = nc::Vector2::Rotate(force, nc::DegreesToRadians(m_owner->m_transform.angle));

	RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
	if(component)
	{
		component->ApplyForce(force);
	}

	//Check for coin contact
	auto coinContacts = m_owner->GetContactsWithTag("coin");
	for (auto contact : coinContacts) 
	{
		contact->m_flags[GameObject::eFlags::DESTROY] = true;
		// play coin sound
	}
}

}