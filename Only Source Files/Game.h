#pragma once
#include "Text.h"
#include "Structures.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <map>

#define WIDTH 1000
#define HEIGHT 800

class Game
{
private:
    //SDL data members
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;
    SDL_Texture* picture = nullptr;
    SDL_Surface* icon = nullptr;
    SDL_Rect to;
    SDL_Rect from;
    //Text data member
    Text* text = nullptr;
    //Map / vector data members
    std::map<std::string, SDL_Rect> images;
    std::map<Colors, SDL_Color> colors;
    std::map<Language, Qs> questions;
    std::map<Language, Pr> prize;
    std::vector<int> used;

    line l;
    int q = -1;
    std::string searchName = "";
    Options options;
    Language language = HUN;
    int fontType = 0;
    bool end = false;
    bool start = false;
    bool read = false;
    int display = 1;
    int OnButton = 0;
    int o = 0;
    int mode = 0;
    int counter = 0;
    int temp;
    int fixMoney = 0;
    bool cashout = false;
    int money;
    int time = 0;
    std::string strTime;
    Player player;
    //Init Methodes
    void Init_Images();
    void Init_Colors();
    void Init_Prize();
    //Methodes
    Qs Read(Language lan);
    Pr Get_Prize(Language lan);
    bool AlreadyUsed();
    int Random(int from, int to);
    line Get_Line();
    int FindHalfOfString(std::string str);
    void Get_RandomQuestion();
    void Render_Precentage(int x1, int x2, int x3, int x4);
    void Render_Help2(int x, bool help);
    void Render_Help3();

    void Sort_Players(std::vector<Player>& vec, int option);
    void Sort_Vec(std::vector<Player>& vec);
    void Swap(Player& x, Player& y);
public:
    //Constructor - Destructor
    Game();
    ~Game();
    //Methodes
    void Init_Questions();
    bool Answer(std::string str);
    int Get_GoodAnswerNum();
    void Get_Question();
    void Reset();
    void Render_OptionImage();
    int Check_NameLength(std::string str);
    void WriteResults();
    //Render methodes
    void Render_Present();
    void Render_Logo();
    void Render_Background();
    void Render_Texts();
    void Render_Arrow();
    //RENDER START
    void Render_StartButton(int x, Colors c);
    void Render_StartButtons();
    void Render_Start();
    //Render SELECT
    void Render_SelectButton(int x, Colors c);
    void Render_SelectButtons();
    void Render_Select();
    void Render_InputField();
    //Render IN-GAME
    void Render_InGameButton(int x, Colors c);
    void Render_InGameButtons();
    void Render_InGame();
    void Render_PrizeBar();
    void Render_PrizeTexts();
    void Render_PrizeBackground();
    void Render_Prize();
    void Render_Helps();
    void Render_Bag();
    void Render_CashOut();
    void Render_FixCashOut();
    void Start_Help1();
    void Start_Help2();
    void Start_Help3();
    void OptionSave();
    //Option page
    void Render_OptionSetting();
    void Render_OptionFont();
    void Render_OptionLanguage();
    void Render_Option();
    void Render_OptionMusic();
    void Render_OptionChunk();
    void Render_OptionSave(Colors c);
    void Render_OptionLeave(Colors c);
    //LeaderBoards
    void Render_Leaderboards();
    void Render_LB_Texts();
    void Render_LB_BG(int x);
    void Render_LB_HelpTexts();
    void Render_LB_Players();
    void Render_LB_PlayerText(std::vector<Player> vec, int mode);
    void Render_LB_BackGround();
    //Results
    void Render_Results();
    void Render_Results_InputField();
    void Render_Results_HelpTexts();
    void Render_Results_Player();
    void Render_Results_Texts();
    //Public data member
    Answers answer = { false, false, false, false };
    Helps helps = { true, true, true };
    //Setter
    void Set_Language(Language language) { this->language = language; }
    void Set_Display(int x) { this->display = x; }
    void Set_OnButton(int x) { this->OnButton = x; }
    void Set_Mode(int x) { this->mode = x; this->player.mode = x; }
    void Set_Option(int x) { this->o = x; }
    void Set_Temp(int x) { this->temp = x; }
    void Set_FixMoney();
    void Set_Start(bool l) { this->start = l; }
    void Set_End(bool l) { this->end = l; }
    void Set_Time(int t) { this->time = t; }
    void Set_StrTime(std::string t) { this->strTime = t; }
    void Set_PlayerCounter(int x) { this->player.counter = x; }
    void Set_Player(Player p) { this->player = p; }
    void Set_Money(int x) { this->money = x; }
    //Getter
    int Get_Display() { return this->display; }
    int Get_OnButton() { return this->OnButton; }
    int Get_Mode() { return this->mode; }
    int Get_Option() { return this->o; }
    int Get_Temp() { return this->temp; }
    int Get_MusicVolume() { return this->options.musicVolume % 11; }
    int Get_ChunkVolume() { return this->options.chunkVolume % 11; }
    bool Get_CashOut() { return this->cashout; }
    int Get_Counter() { return this->counter; }
    bool Get_Start() { return this->start; }
    bool Get_End() { return this->end; }
    int Get_FixMoney() { return fixMoney; }
    int Get_Time() { return time; }
    int Get_Money() { return money; }
    std::string Get_StrTime() { return strTime; }
    Player Get_Player() { return player; }
    Language Get_Language() { return this->language; }
    std::string Get_Name() { return this->player.name; }
    std::string Get_SearchName() { return searchName; }
    //Addto
    void AddTo_LanguageOption(int x) { this->options.languageOption += x; }
    void AddTo_FontOption(int x) { this->options.typeOption += x; }
    void AddTo_MusicVolume(int x) { this->options.musicVolume += x; }
    void AddTo_ChunkVolume(int x) { this->options.chunkVolume += x; }
    void AddTo_Name(char c) { this->player.name += c; }
    void AddTo_Counter() { this->counter++; }
    void AddTo_SearchName(char c) { searchName += c; }
    //Delete
    void DeleteFrom_Name() { this->player.name = player.name.substr(0, player.name.length() - 1); }
    void DelteFrom_SearchName() { this->searchName = searchName.substr(0, searchName.length() - 1); }
    //Exception
    class GAME_EXCEPTION : public std::exception {
    private:
        std::string msg;
    public:
        GAME_EXCEPTION(std::string msg) : msg(msg) {}
        const char* what() {
            return msg.c_str();
        }
    };
};