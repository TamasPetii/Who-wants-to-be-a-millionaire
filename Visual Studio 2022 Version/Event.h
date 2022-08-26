#pragma once
#include "Game.h"
#include "Sound.h"
#include "Structures.h"
class Event
{
private:
	Game* game = nullptr;
	Sound* sound = nullptr;
public:
	Event(Game*& game, Sound*& sound) : game(game), sound(sound) {}
	~Event() { delete game; delete sound; }

	//-Start-//
	void Start();
	void Start_Hover(int button, int on, Colors c);
	void NewGame_Click();
	void LeaderBoard_Click();
	void Results_Click();

	//-Select-//
	void Select();
	void Select_Hover(int button, int on, Colors c);
	void StartGame_Click();
	void Mode_Click(int mode);
	void TextField();

	//-InGame-//
	void InGame();
	void InGame_Hover(int button, int on, Colors c);
	void Help_Click(int help);
	void Good_Answer(int button);
	void Bad_Answer(int button);
	void NewQuestion();
	void CashOut();
	void CashOut_OK();
	void CashOut_Click();

	//-LeaderBoard-//
	void LeaderBoard();

	//-Results-//
	void Results();
	void TextField_Results();
	void Ok();

	//-Option-//
	void Option();
	void Option_Hover(int button, int on, Colors c);
	void Option_Click(int option, int num);
	void Save_Click();
	void Leave_Click();

	void Arrow_Click(int display);

	//Keyboard event
	void Alphabetic_Keyboard(int keyType);
	void Number_Keyboard(int keyType);
	void Delete_Keyboard();
	void Alphabetic_Keyboard_Results(int keyType);
	void Number_Keyboard_Results(int keyType);
	void Delete_Keyboard_Results();


	//Getter
	Game* Get_Game() { return game; }

	bool caps = false;
	bool name = false;
	bool search = false;
};