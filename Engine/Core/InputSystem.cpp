#include "pch.h"
#include "InputSystem.h"

bool nc::InputSystem::Startup()
{
	const Uint8* keystate = SDL_GetKeyboardState(&m_numKeys);
	m_keystate = new Uint8[m_numKeys];
	m_prevKeystate = new Uint8[m_numKeys];
	memcpy(m_keystate, keystate, m_numKeys);
	memcpy(m_prevKeystate, keystate, m_numKeys);

	return true;
}

void nc::InputSystem::Shutdown()
{
	delete[] m_keystate;
	delete[] m_prevKeystate;
}

void nc::InputSystem::Update()
{
	memcpy(m_prevKeystate, m_keystate, m_numKeys);
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate, keystate, m_numKeys);
}


bool nc::InputSystem::GetButtonDown(int id)
{
	//Return keystate at m_keystate[id]
	return m_keystate[id];
}

bool nc::InputSystem::GetPreviousButtonDown(int id)
{
	return m_prevKeystate[id];
}

nc::InputSystem::eButtonState nc::InputSystem::GetButtonState(int id)
{
	eButtonState state = eButtonState::IDLE;

	bool buttonDown = GetButtonDown(id);
	bool prevButtonDown = GetPreviousButtonDown(id);

	if (buttonDown)
	{
		state = (prevButtonDown) ? nc::InputSystem::eButtonState::HELD : nc::InputSystem::eButtonState::PRESSED ;
	}
	else
	{
		state = (prevButtonDown) ? nc::InputSystem::eButtonState::RELEASED : nc::InputSystem::eButtonState::IDLE;
	}

	return state;
}