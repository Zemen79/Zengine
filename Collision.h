#pragma once

#include "GameObject.h"

namespace Zen {
	struct Collision
	{
		static bool RectRect(GameObject* a, GameObject* b);

		static bool CircleCircle(GameObject* a, GameObject* b);

		static bool CircleRect(GameObject* circle, GameObject* rect);

		static void ElasticCollision(Zen::GameObject* a, Zen::GameObject* b);

		static bool TouchTop(Zen::GameObject* a, Zen::GameObject* b);
		static bool TouchBottom(Zen::GameObject* a, Zen::GameObject* b);
		static bool TouchLeft(Zen::GameObject* a, Zen::GameObject* b);
		static bool TouchRight(Zen::GameObject* a, Zen::GameObject* b);
	};
}