#pragma once

#include "Collision.h"
#include "InputManager.h"
#include "Audio.h"
#include "Texture2D.h"
#include "SpriteBatch.h"

#include <SDL\SDL.h>

namespace Zen {
	class Button
	{
	public:
		Button();
		~Button();

		void Init(Texture2D texture, const glm::vec2& position, const glm::vec2& size);

		void Update(InputManager& inputManager, SoundEffect effect);

		void Draw(SpriteBatch& spriteBatch);

	private:

		Collision _collision;
	};
}
