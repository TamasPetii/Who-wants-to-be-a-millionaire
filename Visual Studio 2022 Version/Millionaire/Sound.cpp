#include "Sound.h"

Sound::Sound() {
	Mix_Init(0);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	clickSound = Mix_LoadWAV("./sounds/Click.wav"); if (!clickSound) throw SOUND_EXCEPTION("Couldn't load Audience.wav");
	hoverSound = Mix_LoadWAV("./sounds/Hover.wav"); if (!hoverSound) throw SOUND_EXCEPTION("Couldn't load Hower.wav");
	errorSound = Mix_LoadWAV("./sounds/Error.wav"); if (!errorSound) throw SOUND_EXCEPTION("Couldn't load Error.wav");
}

Sound::~Sound() {
	Mix_FreeMusic(music);
	Mix_FreeChunk(clickSound);
	Mix_FreeChunk(hoverSound);
	Mix_FreeChunk(errorSound);
	Mix_Quit();
}

void Sound::playStartSound() {
	Mix_HaltMusic();
	if(music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/Start.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load Start.wav");
	
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playSelectSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/Select.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load Select.wav");

	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playNewQuestionSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/NewQuestion.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load NewQuestion.wav");

	Mix_PlayMusic(music, 0);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playQuestionBgSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/QuestionBG.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load QuestionBG.wav");

	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playGoodAnswerSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/GoodAnswer.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load GoodAnswer.wav");

	Mix_PlayMusic(music, 0);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playBadAnswerSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/BadAnswer.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load BadAnswer.wav");

	Mix_PlayMusic(music, 0);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playCallSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/Call.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load Call.wav");

	Mix_PlayMusic(music, 0);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playAudienceSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/Audience.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load Audience.wav");

	Mix_PlayMusic(music, 0);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playFiftySound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/50.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load 50.wav");

	Mix_PlayMusic(music, 0);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playSettingsSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/Settings.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load Settings.wav");

	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playCashOutSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/CashOut.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load CashOut.wav");

	Mix_PlayMusic(music, 0);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playLeaderBoardSound() {
	Mix_HaltMusic();
	if (music) Mix_FreeMusic(music);

	music = Mix_LoadMUS("./sounds/Leaderboard.wav"); if (!music) throw SOUND_EXCEPTION("Couldn't load Leaderboard.wav");

	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(MusicVolume);
}

void Sound::playClickSound() {
	Mix_PlayChannel(-1, clickSound, 0);
	Mix_VolumeChunk(clickSound, ChunkVolume);
}

void Sound::playHoverSound() {
	Mix_PlayChannel(-1, hoverSound, 0);
	Mix_VolumeChunk(hoverSound, ChunkVolume * 10);
}

void Sound::playErrorSound() {
	Mix_PlayChannel(-1, errorSound, 0);
	Mix_VolumeChunk(errorSound, ChunkVolume);
}