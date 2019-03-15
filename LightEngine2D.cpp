#include "LightEngine2D.h"

#include <iostream>

namespace Zen {
	LightEngine2D::LightEngine2D()
	{
	}

	LightEngine2D::~LightEngine2D()
	{
	}

	void LightEngine2D::Add(const glm::vec2& position, float size, const glm::vec3& color, float intensity)
	{
		lightON = true;

		if (lightON)
		{
			if (m_lights.size() < (unsigned int)m_MAX_NUM_LIGHTS)
			{
				m_lights.push_back(std::make_shared<Light>(position, size, color, intensity));
			}
		}
	}

	void LightEngine2D::Update(Shader* shader)
	{
		if (lightON == true)
		{
			shader->Bind();

			shader->SetInteger("u_numLights", m_lights.size());
			shader->SetBool("u_LightON", lightON);

			for (unsigned int i = 0; i < m_lights.size(); i++)
			{
				std::shared_ptr<Light> light = m_lights[i];

				shader->SetVector2f("u_lights[" + std::to_string(i) + "].position", light->position);
				shader->SetFloat("u_lights[" + std::to_string(i) + "].size", light->size);
				shader->SetVector3f("u_lights[" + std::to_string(i) + "].color", light->color);
				shader->SetFloat("u_lights[" + std::to_string(i) + "].intensity", light->intensity);
			}

			shader->Unbind();
		}
	}

	void LightEngine2D::Remove(int index)
	{
		m_lights.erase(m_lights.begin() + index);
	}
}