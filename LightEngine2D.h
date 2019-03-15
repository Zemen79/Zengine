#pragma once

#include <vector>
#include <memory>

#include <glm\glm.hpp>

#include "Light.h"
#include "ResourcesManager.h"

namespace Zen {

	class LightEngine2D
	{
	public:
		LightEngine2D();
		~LightEngine2D();

		void Add(const glm::vec2& position, float size, const glm::vec3& color, float intensity);

		void Remove(int index);

		void Update(Shader* shader);

		void SetPosition(int index, const glm::vec2& position) { m_lights[index]->position = position; }

		const std::vector<std::shared_ptr<Light>>& GetLights() const { return m_lights; }

	private:
		std::vector<std::shared_ptr<Light>> m_lights;
		bool lightON = false;
		const int m_MAX_NUM_LIGHTS = 200;
	};
}