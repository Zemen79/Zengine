#include "Audio.h"

namespace Zen {
	/// SOUND EFFECTS
	void SoundEffect::Play(int loops)
	{
		if (Mix_PlayChannel(-1, _chunk, loops) == -1)
		{
			if (Mix_PlayChannel(0, _chunk, loops) == -1)
			{
				Error("Mix_PlayChannel Error: " + std::string(Mix_GetError()));
			}
		}
	}

	/// MUSIC
	void Music::Play(int loops)
	{
		Mix_PlayMusic(_music, loops);
	}

	void Music::Pause()
	{
		Mix_PauseMusic();
	}

	void Music::Stop()
	{
		Mix_HaltMusic();
	}

	void Music::Resume()
	{
		Mix_ResumeMusic();
	}

	/// AUDIO ENGINE
	Audio::Audio()
	{
	}

	Audio::~Audio()
	{
		Destroy();
	}

	void Audio::Init()
	{
		if (_isInitialized)
		{
			Error("Tried to initialize audio twice.");
		}

		if (Mix_Init(MIX_INIT_MP3) == -1)
		{
			Error("Mix_OpenAudio Error: " + std::string(Mix_GetError()));
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		{
			Error("Mix_OpenAudio Error: " + std::string(Mix_GetError()));
		}

		_isInitialized = true;
	}

	void Audio::Destroy()
	{
		if (_isInitialized)
		{
			_isInitialized = false;

			Mix_Quit();
		}
	}

	SoundEffect Audio::LoadSoundEffect(const std::string & filePath)
	{
		SoundEffect effect;

		// find the audio in cache
		auto it = _effectMap.find(filePath);
		if (it == _effectMap.end())
		{
			// failed to find the audio, so load the audio
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			// check for error
			if (chunk == nullptr)
			{
				Error("Mix_Chunk Error: " + std::string(Mix_GetError()));
			}

			effect._chunk = chunk;
			_effectMap[filePath] = chunk;
		}
		else {
			effect._chunk = it->second;
		}

		return effect;
	}

	Music Audio::LoadMusic(const std::string & filePath)
	{
		Music music;

		// find the audio in cache
		auto it = _musicMap.find(filePath);
		if (it == _musicMap.end())
		{
			// failed to find the audio, so load the audio
			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
			// check for error
			if (mixMusic == nullptr)
			{
				Error("Mix_Music Error: " + std::string(Mix_GetError()));
			}

			music._music = mixMusic;
			_musicMap[filePath] = mixMusic;
		}
		else {
			music._music = it->second;
		}

		return music;
	}
}