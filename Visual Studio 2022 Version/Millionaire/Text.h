#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <exception>
#include <string>
class Text
{
private:
    //SDL/TTF data members
    SDL_Renderer* render = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;
    TTF_Font* font = nullptr;
    SDL_Rect to = {0,0,0,0};
    void Get_Text(std::string str, int fontType, int fontSize, SDL_Color color);
    void Copy_Text(int x, int y);
    void Copy_Text_Centered(int x, int y);
    void Copy_Text_YCentered(int x, int y);
    void Clear_Texture_Surface();
public:
    //Constructor
    Text(SDL_Renderer*& render);
    ~Text();
    //Methodes
    void Render_Text(std::string str, int fontType, int fontSize, SDL_Color color, int x, int y);
    void Render_Text_Centered(std::string str, int fontType, int fontSize, SDL_Color color, int x, int y);
    void Render_Text_YCentered(std::string str, int fontType, int fontSize, SDL_Color color, int x, int y);
    int Check_Length(std::string str, int fontType, int fontSize);
    //Exception
    class TEXT_EXCEPTION : public std::exception {
    private:
        std::string msg;
    public:
        TEXT_EXCEPTION(std::string msg) : msg(msg) {}
        const char* what() {
            return msg.c_str();
        }
    };
};
