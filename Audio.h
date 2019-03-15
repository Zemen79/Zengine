#pragma once

#include <SDL\SDL_mixer.h>

#include <string>
#include <map>

#include "Error.h"

namespace Zen {
	class SoundEffect
	{
	public:
		friend class Audio;

		void Play(int loops = 0);

		void SetVolume(int volume) { Mix_VolumeChunk(_chunk, volume); }

	private:
		Mix_Chunk* _chunk = nullptr;
	};

	class Music
	{
	public:
		friend class Audio;

		void Play(int loops = 0);

		static void Pause();
		static void Stop();
		static void Resume();

	private:
		Mix_Music* _music = nullptr;
	};
	class Audio
	{
	public:
		Audio();
		~Audio();

		void Init();
		void Destroy();

		SoundEffect LoadSoundEffect(const std::string& filePath);
		Music LoadMusic(const std::string& filePath);

	private:
		std::map<std::string, Mix_Chunk*> _effectMap;
		std::map<std::string, Mix_Music*> _musicMap;

		bool _isInitialized = false;
	};
}