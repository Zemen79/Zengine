#include "Box2DBody.h"

namespace Zen {

	b2Body* Box2DBody::CreateBox(b2World * world, const glm::vec2 & position, const glm::vec2 & size, bool isStatic)
	{
		// create body
		b2BodyDef bodyDef;
		if (isStatic)
		{
			bodyDef.type = b2_staticBody;
		}
		else
		{
			bodyDef.type = b2_dynamicBody;
		}
		bodyDef.position.Set(position.x, position.y);

		// create shape
		b2PolygonShape boxShape;
		boxShape.SetAsBox(size.x / 2.0f, size.y / 2.0f);

		// create fixture
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.1f;

		return world->CreateBody(&bodyDef)->CreateFixture(&fixtureDef)->GetBody();
	}

	b2Body* Box2DBody::CreateCircle(b2World* world, const glm::vec2& position, const glm::vec2& size,
		bool isStatic, short cBits, short mBits)
	{
		// create body
		b2BodyDef bodyDef;
		if (isStatic)
		{
			bodyDef.type = b2_staticBody;
		}
		else
		{
			bodyDef.type = b2_dynamicBody;
		}
		bodyDef.position.Set(position.x, position.y);

		// create shape
		b2CircleShape circleShape;
		circleShape.m_p.Set(0.0f, 0.0f);
		circleShape.m_radius = size.x / 2.0f;

		// create fixture
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.1f;

		return world->CreateBody(&bodyDef)->CreateFixture(&fixtureDef)->GetBody();
	}

}