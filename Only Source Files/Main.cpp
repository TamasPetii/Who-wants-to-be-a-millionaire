#define SDL_MAIN_HANDLED
#include "Event.h"
#include "Time.h"
#include <thread>

Click click = { false, 0, 0 };
Motion motion = { false, 0, 0 };
Key key = { false, -1 };
bool quit = false;

void gameThread(Event* ev) {
    srand(time(NULL));
    
    ev->Start();

    while (!quit) {
        if (click.event) {
            //Settings
            if (click.x >= 835 && click.x <= 960 && click.y >= 5 && motion.y < 130) {
                ev->Option();
            }

            if (ev->Get_Game()->Get_Display() == 1) {
                //New ev->Get_Game()
                if (click.x >= 300 && click.x <= 700 && click.y >= 540 && click.y < 615) {
                    ev->NewGame_Click();
                }
                else if (click.x >= 300 && click.x <= 700 && click.y >= 630 && click.y < 705) {
                    ev->LeaderBoard_Click();
                }
                else if (click.x >= 300 && click.x <= 700 && click.y >= 720 && click.y < 795) {
                    ev->Results_Click();
                }
            }
            else if (ev->Get_Game()->Get_Display() == 2) {
                //Click on Name text field
                if (click.x >= 355 && click.x <= 645 && click.y >= 665 && click.y < 700) {
                    ev->TextField();
                    key.type = -1;
                }
                //Not Click on Name text field
                else if (ev->name && !(click.x >= 355 && click.x <= 645 && click.y >= 665 && click.y < 700)) {
                    ev->name = false;
                    key.type = -1;
                }
                //Click on Arrow on display 2
                if (click.x >= 45 && click.x <= 202 && click.y >= 10 && click.y < 130) {
                    ev->Arrow_Click(2);
                }
                //Click on Normal
                else if (ev->Get_Game()->Get_Mode() != 1 && click.x >= 25 && click.x <= 325 && click.y >= 540 && click.y < 615) {
                    ev->Mode_Click(1);
                }
                //Click on Medium
                else if (ev->Get_Game()->Get_Mode() != 2 && click.x >= 350 && click.x <= 650 && click.y >= 540 && click.y < 615) {
                    ev->Mode_Click(2);
                }
                //Click on Hard
                else if (ev->Get_Game()->Get_Mode() != 3 && click.x >= 675 && click.x <= 975 && click.y >= 540 && click.y < 615) {
                    ev->Mode_Click(3);
                }
                //Click on Start ev->Get_Game()
                else if (click.x >= 350 && click.x <= 650 && click.y >= 720 && click.y < 795) {
                    ev->StartGame_Click();
                }
            }
            else if (ev->Get_Game()->Get_Display() == 3) {
                //Click on Arrow on display 3
                if (click.x >= 45 && click.x <= 202 && click.y >= 10 && click.y < 130) {
                    ev->Arrow_Click(3);
                }
                //Click on GREEN OK
                else if (ev->Get_Game()->Get_CashOut() && click.x >= 355 && click.x <= 405 && click.y >= 320 && click.y < 370) {
                    ev->CashOut_OK();
                }
                //Click on RED X
                else if (ev->Get_Game()->Get_CashOut() && click.x >= 595 && click.x <= 655 && click.y >= 320 && click.y < 370) {
                    ev->CashOut_Click();
                }
                //Click on bag
                else if (click.x >= 900 && click.x <= 975 && click.y >= 700 && click.y < 775) {
                    ev->CashOut_Click();
                }
                //Click on A button
                else if (!ev->Get_Game()->answer.a && click.x >= 150 && click.x <= 490 && click.y >= 650 && click.y < 700) {
                    ev->Get_Game()->Answer("A") ? ev->Good_Answer(1) : ev->Bad_Answer(1);
                }
                //Click on B button
                else if (!ev->Get_Game()->answer.b && click.x >= 510 && click.x <= 850 && click.y >= 650 && click.y < 700) {
                    ev->Get_Game()->Answer("B") ? ev->Good_Answer(2) : ev->Bad_Answer(2);
                }
                //Click on C button
                else if (!ev->Get_Game()->answer.c && click.x >= 150 && click.x <= 490 && click.y >= 725 && click.y < 775) {
                    ev->Get_Game()->Answer("C") ? ev->Good_Answer(3) : ev->Bad_Answer(3);
                }
                //Click on D button
                else if (!ev->Get_Game()->answer.d && click.x >= 510 && click.x <= 850 && click.y >= 725 && click.y < 775) {
                    ev->Get_Game()->Answer("D") ? ev->Good_Answer(4) : ev->Bad_Answer(4);
                }
                //Click on 50/50 help
                else if (ev->Get_Game()->helps.help1 && click.x >= 50 && click.x <= 230 && click.y >= 140 && click.y < 260) {
                    ev->Help_Click(1);
                }
                //Click on Ask a Friend help
                else if (ev->Get_Game()->helps.help2 && click.x >= 50 && click.x <= 230 && click.y >= 270 && click.y < 390) {
                    ev->Help_Click(2);
                }
                //Click on Ask the Audience help
                else if (ev->Get_Game()->helps.help3 && click.x >= 50 && click.x <= 230 && click.y >= 400 && click.y < 520) {
                    ev->Help_Click(3);
                }
            }
            else if(ev->Get_Game()->Get_Display() == 4){
                //Click on Save button
                if (click.x >= 300 && click.x <= 700 && click.y >= 600 && click.y < 675) {
                    ev->Save_Click();
                }
                //Click on Leave button
                else if (click.x >= 300 && click.x <= 700 && click.y >= 700 && click.y < 775) {
                    ev->Leave_Click();
                }
                //Language left arrow
                else if (click.x >= 510 && click.x <= 535 && click.y >= 210 && click.y < 235) {
                    ev->Option_Click(1, -1);
                }
                //Language right arrow
                else if (click.x >= 750 && click.x <= 775 && click.y >= 210 && click.y < 235) {
                    ev->Option_Click(1, 1);
                }
                //Font type left arrow
                else if (click.x >= 510 && click.x <= 535 && click.y >= 270 && click.y < 295) {
                    ev->Option_Click(2, -1);
                }
                //Font type right arrow
                else if (click.x >= 750 && click.x <= 775 && click.y >= 270 && click.y < 295) {
                    ev->Option_Click(2, 1);
                }
                //Music volume left arrow
                else if (click.x >= 510 && click.x <= 535 && click.y >= 330 && click.y < 355) {
                    ev->Option_Click(3, -1);
                }
                //Music volume right arrow
                else if (click.x >= 750 && click.x <= 775 && click.y >= 330 && click.y < 355) {
                    ev->Option_Click(3, 1);
                }
                //Chunk volume left arrow
                else if (click.x >= 510 && click.x <= 535 && click.y >= 390 && click.y < 415) {
                    ev->Option_Click(4, -1);
                }
                //Chunk volume right arrow
                else if (click.x >= 750 && click.x <= 775 && click.y >= 390 && click.y < 415) {
                    ev->Option_Click(4, 1);
                }
            }
            else if (ev->Get_Game()->Get_Display() == 5) {
                //Click on Arrow on display 5
                if (click.x >= 45 && click.x <= 202 && click.y >= 10 && click.y < 130) {
                    ev->Arrow_Click(5);
                }
            }
            else if (ev->Get_Game()->Get_Display() == 6) {
                //Click on Arrow on display 6
                if (click.x >= 45 && click.x <= 202 && click.y >= 10 && click.y < 130) {
                    ev->Arrow_Click(6);
                }
                //Click on Search Name text field
                if (click.x >= 355 && click.x <= 595 && click.y >= 65 && click.y < 100) {
                    ev->TextField_Results();
                    key.type = -1;
                }
                //Not Click on Name text field
                else if (ev->search && !(click.x >= 355 && click.x <= 645 && click.y >= 65 && click.y < 100)) {
                    ev->search = false;
                    key.type = -1;
                }
                //Click on GREEN OK
                if (click.x >= 605 && click.x <= 640 && click.y >= 65 && click.y < 100) {
                    ev->Ok();
                }
            }
            click.event = false;
        }
        if (motion.event) {
            if (ev->Get_Game()->Get_Display() == 1) {
                //Hover on Newev->Get_Game() Button
                if (ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 300 && motion.x <= 700 && motion.y >= 540 && motion.y < 615) {
                    ev->Start_Hover(1, 1, ORANGE);
                }
                //Not hover on Newev->Get_Game() Button
                else if (ev->Get_Game()->Get_OnButton() == 1 && !(motion.x >= 300 && motion.x <= 700 && motion.y >= 540 && motion.y < 615)) {
                    ev->Start_Hover(1, 0, BLUE);
                }
                //Hover on LeaderBoard Button
                else if (ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 300 && motion.x <= 700 && motion.y >= 630 && motion.y < 705) {
                    ev->Start_Hover(2, 2, ORANGE);
                }
                //Not hover on LeaderBoard Button
                else if (ev->Get_Game()->Get_OnButton() == 2 && !(motion.x >= 300 && motion.x <= 700 && motion.y >= 630 && motion.y < 705)) {
                    ev->Start_Hover(2, 0, BLUE);
                }
                //Hover on Results Button
                else if (ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 300 && motion.x <= 700 && motion.y >= 720 && motion.y < 795) {
                    ev->Start_Hover(3, 3, ORANGE);
                }
                //Not hover on Results Button
                else if (ev->Get_Game()->Get_OnButton() == 3 && !(motion.x >= 300 && motion.x <= 700 && motion.y >= 720 && motion.y < 795)) {
                    ev->Start_Hover(3, 0, BLUE);
                }
            }
            else if (ev->Get_Game()->Get_Display() == 2) {
                //Hover on Normal Button
                if (ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 25 && motion.x <= 325 && motion.y >= 540 && motion.y < 615) {
                    ev->Select_Hover(1, 1, ORANGE);
                }
                //Not hover on Normal Button
                else if (ev->Get_Game()->Get_OnButton() == 1 && !(motion.x >= 25 && motion.x <= 325 && motion.y >= 540 && motion.y < 615)) {
                    ev->Select_Hover(1, 0, BLUE);
                }
                //Hover on Medium Button
                else if (ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 350 && motion.x <= 650 && motion.y >= 540 && motion.y < 615) {
                    ev->Select_Hover(2, 2, ORANGE);
                }
                //Not hover on Medium Button
                else if (ev->Get_Game()->Get_OnButton() == 2 && !(motion.x >= 350 && motion.x <= 650 && motion.y >= 540 && motion.y < 615)) {
                    ev->Select_Hover(2, 0, BLUE);
                }
                //Hover on Hard Button
                else if (ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 675 && motion.x <= 975 && motion.y >= 540 && motion.y < 615) {
                    ev->Select_Hover(3, 3, ORANGE);
                }
                //Not hover on Hard Button
                else if (ev->Get_Game()->Get_OnButton() == 3 && !(motion.x >= 675 && motion.x <= 975 && motion.y >= 540 && motion.y < 615)) {
                    ev->Select_Hover(3, 0, BLUE);
                }
                //Hover on Start Button
                else if (ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 350 && motion.x <= 650 && motion.y >= 720 && motion.y < 795) {
                    ev->Select_Hover(4, 4, ORANGE);
                }
                //Not hover on Start Button
                else if (ev->Get_Game()->Get_OnButton() == 4 && !(motion.x >= 350 && motion.x <= 650 && motion.y >= 720 && motion.y < 795)) {
                    ev->Select_Hover(4, 0, BLUE);
                }
            }
            else if (ev->Get_Game()->Get_Display() == 3) {
                //Hover on A Button
                if (!ev->Get_Game()->answer.a && ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 150 && motion.x <= 490 && motion.y >= 650 && motion.y < 700) {
                    ev->InGame_Hover(1, 1, ORANGE);
                }
                //Not hover on A Button
                else if (!ev->Get_Game()->answer.a &&  ev->Get_Game()->Get_OnButton() == 1 && !(motion.x >= 150 && motion.x <= 490 && motion.y >= 650 && motion.y < 700)) {
                    ev->InGame_Hover(1, 0, BLUE);
                }
                //Hover on B Button
                else if (!ev->Get_Game()->answer.b && ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 510 && motion.x <= 850 && motion.y >= 650 && motion.y < 700) {
                    ev->InGame_Hover(2, 2, ORANGE);
                }
                //Not hover on B Button
                else if (!ev->Get_Game()->answer.b && ev->Get_Game()->Get_OnButton() == 2 && !(motion.x >= 510 && motion.x <= 850 && motion.y >= 650 && motion.y < 700)) {
                    ev->InGame_Hover(2, 0, BLUE);
                }
                //Hover on C Button
                else if (!ev->Get_Game()->answer.c && ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 150 && motion.x <= 490 && motion.y >= 725 && motion.y < 775) {
                    ev->InGame_Hover(3, 3, ORANGE);
                }
                //Not hover on C Button
                else if (!ev->Get_Game()->answer.c && ev->Get_Game()->Get_OnButton() == 3 && !(motion.x >= 150 && motion.x <= 490 && motion.y >= 725 && motion.y < 775)) {
                    ev->InGame_Hover(3, 0, BLUE);
                }
                //Hover on D Button
                else if (!ev->Get_Game()->answer.d && ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 510 && motion.x <= 850 && motion.y >= 725 && motion.y < 775) {
                    ev->InGame_Hover(4, 4, ORANGE);
                }
                //Not hover on D Button
                else if (!ev->Get_Game()->answer.d && ev->Get_Game()->Get_OnButton() == 4 && !(motion.x >= 510 && motion.x <= 850 && motion.y >= 725 && motion.y < 775)) {
                    ev->InGame_Hover(4, 0, BLUE);
                }
            }
            else if (ev->Get_Game()->Get_Display() == 4) {
                //Hover on Save
                if (ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 300 && motion.x <= 700 && motion.y >= 600 && motion.y < 675) {
                    ev->Option_Hover(1, 1, ORANGE);
                }
                //Not hover on Save
                else if (ev->Get_Game()->Get_OnButton() == 1 && !(motion.x >= 300 && motion.x <= 700 && motion.y >= 600 && motion.y < 675)) {
                    ev->Option_Hover(1, 0, GREEN);
                }
                //Hover on Leave
                if (ev->Get_Game()->Get_OnButton() == 0 && motion.x >= 300 && motion.x <= 700 && motion.y >= 700 && motion.y < 775) {
                    ev->Option_Hover(2, 2, ORANGE);
                }
                //Not hover on Leave
                else if (ev->Get_Game()->Get_OnButton() == 2 && !(motion.x >= 300 && motion.x <= 700 && motion.y >= 700 && motion.y < 775)) {
                    ev->Option_Hover(2, 0, RED);
                }
            }
            motion.event = false;
        }
        if (ev->name && key.event) {
            //Click on Caps Lock
            if (key.type == 1073741881) {
                ev->caps ? ev->caps = false : ev->caps = true;
            }
            //Alphabetic click A-Z
            else if (key.type >= 97 && key.type <= 122) {
                ev->Alphabetic_Keyboard(key.type);
            }
            //Click on number 0-9
            else if (key.type >= 45 && key.type <= 57) {
                ev->Number_Keyboard(key.type);
            }
            //Click on BackSpace
            else if (key.type == 8) {
                ev->Delete_Keyboard();
            }
            key.event = false;
        }
        if (ev->search && key.event) {
            //Click on Caps Lock
            if (key.type == 1073741881) {
                ev->caps ? ev->caps = false : ev->caps = true;
            }
            //Alphabetic click A-Z
            else if (key.type >= 97 && key.type <= 122) {
                ev->Alphabetic_Keyboard_Results(key.type);
            }
            //Click on number 0-9
            else if (key.type >= 45 && key.type <= 57) {
                ev->Number_Keyboard_Results(key.type);
            }
            //Click on BackSpace
            else if (key.type == 8) {
                ev->Delete_Keyboard_Results();
            }
            key.event = false;
        }
        Sleep(25);
    }
}

void readThread(Game* game) {
    game->Init_Questions();
}

void timeThread(Time* time, Game* game) {
    bool reset = true;
    while (!quit) {
        if (game->Get_Start()) {
            if (reset) {
                time->Reset();
                reset = false;
            }
            time->Count();
            Sleep(975);
        }
        if (game->Get_End()) {
            reset = true;
            game->Set_End(false);
            game->Set_Time(time->Get_Sec());
            game->Set_StrTime(time->To_String());
        }
        Sleep(25);
    }
}

int main(int argc, char** argv) {
    SDL_SetMainReady();
    Game* game;
    Sound* sound;
    Time* time;
    Event* ev;
    try {
        game = new Game();
        sound = new Sound();
        time = new Time();
        ev = new Event(game, sound);

        std::thread th(gameThread, ev);
        std::thread tr(readThread, game);
        std::thread tt(timeThread, time, game);
        tt.detach();
        th.detach();
        tr.detach();

        SDL_Event event;
        while (!quit) {
            while (SDL_PollEvent(&event)) {
                switch (event.type)
                {          
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }
                    else {
                        key = { true, event.key.keysym.sym };
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        click = { true, event.button.x, event.button.y };
                    }
                    break;
                case SDL_MOUSEMOTION:
                    motion = { true, event.button.x, event.button.y };
                    break;
                }
            }
            Sleep(25);
        }   
    }
    catch (Game::GAME_EXCEPTION& exception) {
        std::cout << exception.what() << std::endl;
        exit(1);
    }
    catch (Text::TEXT_EXCEPTION& exception) {
        std::cout << exception.what() << std::endl;
        exit(1);
    }
    catch (Sound::SOUND_EXCEPTION& exception) {
        std::cout << exception.what() << std::endl;
        exit(1);
    }
    delete ev;
    delete time;
    return 0;
}