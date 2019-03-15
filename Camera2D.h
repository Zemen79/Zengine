#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Shader.h"

namespace Zen {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void Init(int screenWidth, int screenHeight);
		void Update(Shader* shader);
		glm::vec2 ConvertScreenToWorld(glm::vec2 screenCoords);

		// setters
		void SetPosition(const glm::vec2& newPosition) { m_position = newPosition; m_needMatrixUpdate = true; }
		void SetScale(const float newScale) { m_scale = newScale; m_needMatrixUpdate = true; }

		// getters
		glm::vec2 GetPosition() { return m_position; }
		float GetScale() { return m_scale; }
		glm::mat4 GetCameraMatrix() { return m_cameraMatrix; }

	private:
		int m_screenWidth, m_screenHeight;
		bool m_needMatrixUpdate;
		float m_scale;
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;
	};
}
