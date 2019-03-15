#pragma once

namespace Zen {
	class Animation
	{
	public:
		int Animate(int frames, float interval)
		{
			_timer += 0.1f;

			if (_timer > interval)
			{
				_currentFrame++;

				if (_currentFrame > frames)
					_currentFrame = 0;

				_timer = 0;
			}

			return _currentFrame;
		}

	private:
		float _timer;
		int _currentFrame;
	};
}