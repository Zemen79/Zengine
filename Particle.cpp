#include "Particle.h"

namespace Zen {

	Particle::Particle(Texture2D texture, const glm::vec2& position, const glm::vec2& size,
		const glm::vec2& velocity, float rotation, const glm::vec4& color, float life, float decayRate)
		: m_texture(texture), m_position(position), m_size(size), m_velocity(velocity), m_rotation(rotation), m_color(color), m_life(life), m_decayRate(decayRate)
	{
	}

	Particle::~Particle()
	{
	}

	void Particle::Update(float deltaTime)
	{
		m_life -= m_decayRate * deltaTime;
		m_position += m_velocity * deltaTime;
	}

	void Particle::Draw(SpriteBatch& spriteBatch)
	{
		spriteBatch.Submit(m_texture, m_position - m_size / 2.0f, m_size,  m_rotation, glm::vec4(0, 0, 1, 1), m_color);
	}
}