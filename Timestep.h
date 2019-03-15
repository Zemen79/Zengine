#pragma once

namespace Zen {

	struct Timestep
	{
	private:
		float m_fps, m_lastFPS, m_lastTime, m_deltaTime;
	public:
		inline void Init(float initialTime)
		{
			m_fps = 0.0f;
			m_lastFPS = 0.0f;
			m_lastTime = initialTime;
		}

		inline void Update(float currentTime)
		{
			static const int numSamples = 100;
			static float frames[numSamples];
			static int currentFrame = 0;
			static float frameTime = 0;

			frameTime = currentTime - m_lastTime;

			frames[currentFrame % numSamples] = frameTime;

			m_lastTime = currentTime;

			m_deltaTime = frameTime / 60.0f;

			currentFrame++;

			if (currentFrame >= 100)
			{
				float frameTimeAverage = 0;
				for (int i = 0; i < numSamples; i++)
					frameTimeAverage += frames[i];
				frameTimeAverage /= numSamples;

				m_fps = 1000.0f / frameTimeAverage;

				currentFrame = 0;
			}
		}

		inline int GetFPS() const { return (int)m_fps; }
		inline float GetDelta() const { return m_deltaTime; }
	};

}
