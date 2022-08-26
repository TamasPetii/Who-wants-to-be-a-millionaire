#pragma once
#include <SDL_mixer.h>
#include <exception>
#include <string>
class Sound
{
private:
	Mix_Music* music = nullptr;

	Mix_Chunk* clickSound = nullptr;
	Mix_Chunk* hoverSound = nullptr;
	Mix_Chunk* errorSound = nullptr;


	int MusicVolume = 5;
	int ChunkVolume = 5;

public:
	Sound();
	~Sound();

	void Set_MusicVolume(int x) { this->MusicVolume = x; }
	void Set_ChunkVolume(int x) { this->ChunkVolume = x; }
	//Methodes
	void playStartSound();
	void playSelectSound();
	void playNewQuestionSound();
	void playQuestionBgSound();
	void playGoodAnswerSound();
	void playBadAnswerSound();
	void playAudienceSound();
	void playCallSound();
	void playFiftySound();
	void playSettingsSound();
	void playCashOutSound();
	void playLeaderBoardSound();

	void playClickSound();
	void playHoverSound();
	void playErrorSound();
	//Exception
	class SOUND_EXCEPTION : public std::exception {
	private:
		std::string msg;
	public:
		SOUND_EXCEPTION(std::string msg) : msg(msg) {}
		const char* what() {
			return msg.c_str();
		}
	};
};