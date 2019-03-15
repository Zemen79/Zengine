#include "InputManager.h"

namespace Zen {

	void InputManager::Update()
	{
		/// loop through each map and copy over to previous keymap
		for (auto& it : m_keyMap)
		{
			m_previousKeyMap[it.first] = it.second;
		}
	}

	void InputManager::PressKey(unsigned int keyID)
	{
		m_keyMap[keyID] = true;
	}

	void InputManager::ReleaseKey(unsigned int keyID)
	{
		m_keyMap[keyID] = false;
	}

	void InputManager::SetMouseCoords(float x, float y)
	{
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;
	}

	bool InputManager::IsKeyDown(unsigned int keyID)
	{
		auto it = m_keyMap.find(keyID);

		if (it != m_keyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}

	bool InputManager::WasKeyDown(unsigned int keyID)
	{
		auto it = m_previousKeyMap.find(keyID);

		if (it != m_previousKeyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}

	bool InputManager::IsKeyPressed(unsigned int keyID)
	{
		/// check if it was pressed this frame and wasn't last frame
		if (IsKeyDown(keyID) == true && WasKeyDown(keyID) == false)
		{
			return true;
		}

		return false;
	}
}