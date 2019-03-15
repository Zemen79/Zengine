#pragma once

#include <glm\glm.hpp>
#include <unordered_map>

namespace Zen {
	class InputManager
	{
	public:
		void Update();

		void PressKey(unsigned int keyID);
		void ReleaseKey(unsigned int keyID);

		/// returns true if key is being held down
		bool IsKeyDown(unsigned int keyID);

		/// return true if key was just pressed
		bool IsKeyPressed(unsigned int keyID);

		/// returns mouse position
		glm::vec2 GetMouse() const { return m_mouseCoords; }

		/// sets mouse position
		void SetMouseCoords(float x, float y);

	private:

		/// returns true if key was being held down
		bool WasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;
		glm::vec2 m_mouseCoords;
	};
}