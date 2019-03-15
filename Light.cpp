#include "Light.h"

namespace Zen {

	Light::Light(const glm::vec2& position, float size, const glm::vec3& color, float intensity)
		: position(position), size(size), color(color), intensity(intensity)
	{
	}

	Light::~Light()
	{
	}
}