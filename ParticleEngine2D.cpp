#include "ParticleEngine2D.h"

#include <SDL\SDL.h>

namespace Zen
{
	ParticleEngine2D::ParticleEngine2D()
	{
		// random initializer
		srand(SDL_GetTicks());
	}

	ParticleEngine2D::~ParticleEngine2D()
	{
	}

	void ParticleEngine2D::AddParticles(Texture2D texture, const glm::vec2& position,
		const glm::vec2& size, const glm::vec2& velocity, float rotation,
		const glm::vec4& color, float life, float decayRate)
	{
		m_particles.push_back(std::make_shared<Particle>(texture, position, size, velocity, rotation, color, life, decayRate));
	}

	void ParticleEngine2D::Update(float deltaTime)
	{
		// update each particle
		for (unsigned int i = 0; i < m_particles.size(); i++)
		{
			m_particles[i]->Update(deltaTime);

			// delete if not visible anymore	
			if (m_particles[i]->Visible() == false)
			{
				m_particles.erase(m_particles.begin() + i);
			}
		}
	}

	void ParticleEngine2D::Draw(SpriteBatch& spriteBatch)
	{
		for (unsigned int i = 0; i < m_particles.size(); i++)
		{
			m_particles[i]->Draw(spriteBatch);
		}
	}

	// Clear the particles when changing seasons / weather 
	void ParticleEngine2D::Clear()
	{
		for (unsigned int i = 0; i < m_particles.size(); i++)
		{
			m_particles.clear();
		}
	}
}