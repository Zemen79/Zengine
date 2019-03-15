#pragma once
#include "glm/glm.hpp"

namespace Zen {
	
	struct Light
	{
		Light(const glm::vec2& position, float size, const glm::vec3& color = glm::vec3(1.0f), float intensity = 1.0f);
		~Light();

		glm::vec2 position;
		float  size;
		glm::vec3 color;
		float intensity;
	};
}
