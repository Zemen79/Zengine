#pragma once

#include "Texture2D.h"

#include <glm\glm.hpp>

namespace Zen {
	class SpriteSheet
	{
	public:
		SpriteSheet() {}

		SpriteSheet(const Texture2D& texture, const glm::vec2& size, const glm::vec2& tileDims, float animationInteval)
		{
			this->texture = texture;
			this->size = size;
			this->tileDims = tileDims;
			this->animationInterval = animationInteval;
		}

		void Init(const Texture2D& texture, const glm::vec2& size, const glm::vec2& tileDims, float animationInteval)
		{
			this->texture = texture;
			this->size = size;
			this->tileDims = tileDims;
			this->animationInterval = animationInteval;
		}

		void SetTexture(const Texture2D& texture) { this->texture = texture; }
		void SetDimentions(const glm::vec2& tileDims) { this->tileDims = tileDims; }

		glm::vec4 GetUV(int index)
		{
			index -= 1; // so that it starts at 0, because we are ignoring 0 from being
						// drawn as an object in our level, tile sheet starts at 0
			int xTile = index % (int)tileDims.x;
			int yTile = index / (int)tileDims.x;

			glm::vec4 uv;
			uv.x = xTile / tileDims.x;
			uv.y = yTile / tileDims.y;
			uv.z = 1.0f / tileDims.x;
			uv.w = 1.0f / tileDims.y;

			return uv;
		}

		Texture2D texture;
		glm::vec2 size;
		glm::vec2 tileDims;
		float animationInterval;
	};
}