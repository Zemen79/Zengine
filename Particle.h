#pragma once

#include "SpriteBatch.h"

namespace Zen {

	class Particle
	{
	public:
		Particle(Texture2D texture, const glm::vec2& position, const glm::vec2& size,
			const glm::vec2& velocity, float rotation, const glm::vec4& color, float life, float decayRate);
		~Particle();

		void Update(float deltaTime);
		void Draw(SpriteBatch& spriteBatch);

		// getters
		bool Visible() { return(m_life <= 0 ? false : true); }

		void SetRotation(float value) { m_rotation = value; }

	private:
		Texture2D m_texture;
		glm::vec2 m_position;
		glm::vec2 m_size;
		glm::vec2 m_velocity;
		float m_rotation;
		glm::vec4 m_color;
		float m_life;
		float m_decayRate;
	};
}