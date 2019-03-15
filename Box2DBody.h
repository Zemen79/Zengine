#pragma once

#include <Box2D\Box2D.h>

#include <glm/glm.hpp>

namespace Zen {

	using namespace Zen;

	class Box2DBody
	{
	public:
		static b2Body* CreateBox(b2World* world, const glm::vec2& position, const glm::vec2& size,
			bool isStatic);

		static b2Body* CreateCircle(b2World* world, const glm::vec2& position, const glm::vec2& size,
			bool isStatic, short cBits, short mBits);

	private:
		static b2Body* m_body;
		static b2Fixture* m_fixture;
	};

}