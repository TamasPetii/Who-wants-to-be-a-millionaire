#pragma once
#include <iostream>
#include <vector>
#include <string>

enum Language { HUN, ENG, GER };
enum Colors { WHITE, ORANGE, BLUE, GREEN, GREY, RED, PURPLE, BLACK };

struct line {
    std::string difficulty;
    std::string question;
    std::string a;
    std::string b;
    std::string c;
    std::string d;
    std::string answer;
    std::string category;
};

std::ostream& operator<<(std::ostream& s, line l);

std::istream& operator>>(std::istream& s, line& l);


struct Qs {
    std::vector<line> normal;
    std::vector<line> medium;
    std::vector<line> hard;
};

struct Pr {
    std::vector<int> normal;
    std::vector<int> medium;
    std::vector<int> hard;
};

struct Helps {
    bool help1;
    bool help2;
    bool help3;
};

struct Answers {
    bool a;
    bool b;
    bool c;
    bool d;
};

struct Click
{
    bool event;
    int x;
    int y;
};

struct Motion
{
    bool event;
    int x;
    int y;
};

struct Key {
    bool event;
    int type;
};

struct Options {
    int languageOption = 30000;
    int typeOption = 30000;
    int musicVolume = 32994;
    int chunkVolume = 32994;
};

struct Player {
    std::string name = "";
    int mode = 0;
    int time = 0;
    int counter = 0;
    int money = 0;
    std::string strTime = "";
};

std::ostream& operator<<(std::ostream& s, Player p);

std::istream& operator>>(std::istream& s, Player& p);