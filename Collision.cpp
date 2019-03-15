#include "Collision.h"

#include <glm\glm.hpp>
#include "GameObject.h"

namespace Zen {

	bool Collision::RectRect(GameObject* a, GameObject* b)
	{
		if ((a->position.x + a->size.x >= b->position.x &&
			b->position.x + b->size.x >= a->position.x) &&
			(a->position.y + a->size.y >= b->position.y &&
				b->position.y + b->size.y >= a->position.y))
		{
			return true;
		}

		return false;
	}

	bool Collision::CircleCircle(GameObject* one, GameObject* two)
    {
        // first circle
        one->origin = one->position + one->size / 2.0f;
        float x1 = one->origin.x;
        float y1 = one->origin.y;
        float r1 = ((one->size.x + one->size.y) / 2.0f) / 2; // get average size then divide by 2

        // second circle
        two->origin = two->position + two->size / 2.0f;
        float x2 = two->origin.x;
        float y2 = two->origin.y;
        float r2 = ((two->size.x + two->size.y) / 2.0f) / 2; // do the same as r1

        return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) <= (r1 + r2);
    }

    bool Collision::CircleRect(GameObject* circle, GameObject* rect)
    {
        glm::vec2 center(circle->position + circle->size.x / 2.0f);

        glm::vec2 aabb_half_extents(rect->size.x / 2, rect->size.y / 2);
        glm::vec2 aabb_center(rect->position.x + aabb_half_extents.x,
            rect->position.y + aabb_half_extents.y);

        glm::vec2 difference = center - aabb_center;
        glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

        glm::vec2 closest = aabb_center + clamped;

        difference = closest - center;
        return glm::length(difference) < circle->size.x / 2.0f;
    }

	void Collision::ElasticCollision(Zen::GameObject* a, Zen::GameObject* b)
	{
		glm::vec2 v1, v2;

		v1 = ((a->mass - b->mass) * a->velocity + 2 * b->mass*b->velocity) / (a->mass + b->mass);
		v2 = ((b->mass - a->mass) * b->velocity + 2 * a->mass*a->velocity) / (a->mass + b->mass);

		a->velocity = v1;
		b->velocity = v2;
	}

	bool Collision::TouchTop(Zen::GameObject * a, Zen::GameObject * b)
	{
		if (a->position.y + a->size.y >= b->position.y)
		{
			return true;
		}
		
		return false;
	}
	bool Collision::TouchBottom(Zen::GameObject * a, Zen::GameObject * b)
	{
		if (a->position.y <= b->position.y + b->size.y)
		{
			return true;
		}

		return false;
	}
	bool Collision::TouchLeft(Zen::GameObject * a, Zen::GameObject * b)
	{
		if (a->position.x + a->size.x >= b->position.x)
		{
			return true;
		}

		return false;
	}
	bool Collision::TouchRight(Zen::GameObject * a, Zen::GameObject * b)
	{
		if (a->position.x <= b->position.x + b->size.x)
		{
			return true;
		}

		return false;
	}
}