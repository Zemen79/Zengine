#pragma once

#include "Particle.h"
#include <memory>

namespace Zen {
	
	/////////////////////////////////////////////////////////////////////

	class ParticleEngine2D
	{
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		void AddParticles(Texture2D texture, const glm::vec2& position,
			const glm::vec2& size, const glm::vec2& velocity, float rotation,
			const glm::vec4& color, float life, float decayRate);

		void Clear();

		void Update(float deltaTime);

		void Draw(SpriteBatch& spriteBatch);

		std::vector<std::shared_ptr<Particle>>& GetParticles() { return m_particles; }

	private:
		std::vector <std::shared_ptr<Particle>> m_particles;
	};

}

