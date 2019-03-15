#include "Camera2D.h"

namespace Zen {
	Camera2D::Camera2D() :
		m_position(1.0f, 1.0f),
		m_cameraMatrix(1.0f),
		m_scale(1.0f),
		m_needMatrixUpdate(true),
		m_screenWidth(0),
		m_screenHeight(0)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::Init(int screenWidth, int screenHeight)
	{
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_orthoMatrix = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f, -1.0f, 1.0f);
	}

	void Camera2D::Update(Shader*shader)
	{
		shader->Bind();
		shader->SetMatrix4("u_Projection", m_cameraMatrix);
		shader->Unbind();

		if (m_needMatrixUpdate)
		{
			glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_cameraMatrix *= glm::scale(glm::mat4(1.0f), scale);

			m_needMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::ConvertScreenToWorld(glm::vec2 screenCoords)
	{
		// make 0 center
		screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		// scale coordinates
		screenCoords /= m_scale;
		// translate with the camera position
		screenCoords += m_position;

		return screenCoords;
	}
}