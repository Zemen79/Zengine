#pragma once


#include "Texture2D.h"
#include "SpriteBatch.h"

#include <glm/glm.hpp>

namespace Zen {
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void Submit(SpriteBatch& spriteBatch);

		Texture2D texture;
		glm::vec2 position;
		glm::vec2 size;
		glm::vec4 color;
		glm::vec4 uv;
		glm::vec2 velocity;
		glm::vec2 direction;
		float mass;
		glm::vec2 origin;
		float angle;
		bool visible;
		bool solid;
	};
}

