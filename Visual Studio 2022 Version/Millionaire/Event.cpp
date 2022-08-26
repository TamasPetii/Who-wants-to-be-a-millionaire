#include "Event.h"
//---------------------------------------------------Display-:-Start---------------------------------------------------//
void Event::Start() {
    sound->playStartSound();
    game->Set_Display(1);
    game->Render_Start();
}

void Event::Start_Hover(int button, int on, Colors c) {
    sound->playHoverSound();
    game->Set_OnButton(on);
    game->Render_StartButton(button, c);
    game->Render_Present();
}

void Event::NewGame_Click() {
    sound->playClickSound();
    game->Set_Display(2);
    game->Set_OnButton(0);
    game->Render_StartButton(1, GREEN);
    game->Render_Present();
    SDL_Delay(100);
    Select();
}

void Event::LeaderBoard_Click() {
    sound->playClickSound();
    LeaderBoard();
}

void Event::Results_Click() {
    sound->playClickSound();
    Results();
}

//---------------------------------------------------Display-:-Select---------------------------------------------------//

void Event::Select() {
    sound->playSelectSound();
    game->Set_Display(2);
    game->Render_Select();
}

void Event::Select_Hover(int button, int on, Colors c) {
    sound->playHoverSound();
    game->Set_OnButton(on);
    game->Render_SelectButton(button, c);
    game->Render_Present();
}

void Event::Mode_Click(int mode) {
    sound->playClickSound();
    game->Set_Mode(mode);
    game->Render_SelectButtons();
    game->Render_Present();
}

void Event::StartGame_Click() {
    if (game->Get_Mode() == 0 || game->Get_Name() == "") {
        sound->playErrorSound();
    }
    else {
        sound->playClickSound();
        game->Set_Start(true);
        game->Render_SelectButton(4, GREEN);
        game->Set_Display(3);
        game->Set_OnButton(0);
        game->Render_Present();
        SDL_Delay(100);
        NewQuestion();
    }
}

void Event::TextField() {
    sound->playClickSound();
    name = true;
}

void Event::TextField_Results() {
    sound->playClickSound();
    search = true;
}
//---------------------------------------------------Display-:-InGame---------------------------------------------------//

void Event::InGame() {
    sound->playQuestionBgSound();
    game->Set_Display(3);
    game->Render_InGame();
}

void Event::InGame_Hover(int button, int on, Colors c) {
    sound->playHoverSound();
    game->Set_OnButton(on);
    game->Render_InGameButton(button, c);
    game->Render_Present();
}

void Event::Help_Click(int help) {
    if (help == 1) {
        sound->playFiftySound();
        game->helps.help1 = false;
        game->Render_Helps();
        game->Start_Help1();
        Sleep(2000);
    }
    else if (help == 2) {
        sound->playCallSound();
        game->helps.help2 = false;
        game->Render_Helps();
        game->Start_Help2();
        Sleep(100);
    }
    else if (help == 3) {
        sound->playAudienceSound();
        game->helps.help3 = false;
        game->Render_Helps();
        game->Start_Help3();
        Sleep(2100);
    }
    game->Render_Present();
    sound->playQuestionBgSound();
}

void Event::Bad_Answer(int button) {
    sound->playClickSound();
    sound->playBadAnswerSound();
    SDL_Delay(5000);
    game->Render_InGameButton(game->Get_GoodAnswerNum(), GREEN);
    game->Render_InGameButton(button, RED);
    game->Render_Present();
    SDL_Delay(7000);
    game->Render_FixCashOut();
    game->Set_Money(game->Get_FixMoney() * 5);
    CashOut();
}

void Event::Good_Answer(int button) {
    sound->playClickSound();
    sound->playGoodAnswerSound();
    SDL_Delay(5000);
    game->Render_InGameButton(button, GREEN);
    game->Render_Present();
    SDL_Delay(7000);
    game->AddTo_Counter();
    if (game->Get_Counter() == 15) {
        game->Set_FixMoney();
        game->Render_FixCashOut();
        game->Set_Money(game->Get_FixMoney() * 5);
        CashOut();
    }
    else {
        game->Set_FixMoney();
        game->answer = { false, false, false, false };
        NewQuestion();
    }
}


void Event::NewQuestion() {
    sound->playNewQuestionSound();
    game->Get_Question();
    game->Render_Present();
    SDL_Delay(5000);
    sound->playQuestionBgSound();
}

void Event::CashOut() {
    game->Set_Start(false);
    game->Set_End(true);
    sound->playCashOutSound();
    SDL_Delay(7500);
    game->Set_Player({ game->Get_Name() , game->Get_Mode() , game->Get_Time(), game->Get_Counter(), game->Get_Money(),game->Get_StrTime()});
    game->WriteResults();
    game->Reset();
    Start();
}

void Event::CashOut_OK() {
    sound->playClickSound();
    game->Set_Money(game->Get_Counter());
    CashOut();
}

void Event::CashOut_Click() {
    sound->playClickSound();
    game->Render_CashOut();
}

//-----------------------------------------------Display-:-LeaderBoard-----------------------------------------------//

void Event::LeaderBoard() {
    sound->playLeaderBoardSound();
    game->Set_Display(5);
    game->Render_Leaderboards();
}

//-----------------------------------------------Display-:-Results-----------------------------------------------//

void Event::Results() {
    sound->playLeaderBoardSound();
    game->Set_Display(6);
    game->Render_Results();
}

void Event::Ok() {
    sound->playClickSound();
    game->Render_Results_Texts();
    game->Render_Present();
}

//---------------------------------------------------Display-:-Option---------------------------------------------------//

void Event::Option() {
    sound->playClickSound();
    if (game->Get_Option() == 0) {
        sound->playSettingsSound();
        game->Set_Temp(game->Get_Display());
        game->Set_Display(4);
        game->Set_Option(1);
        game->Render_Option();
    }
    else {
        game->Set_Option(0);
        if (game->Get_Temp() == 1) {
            Start();
            game->Render_Texts();
        }
        else if (game->Get_Temp() == 2) {
            Select();
            game->Render_Texts();
        }
        else if (game->Get_Temp() == 3) {
            InGame();
            game->Render_Texts();
        }
        else if (game->Get_Temp() == 5) {
            LeaderBoard();
        }
        else if (game->Get_Temp() == 6) {
            Results();
        }
    }
}

void Event::Option_Hover(int button, int on, Colors c) {
    sound->playHoverSound();
    game->Set_OnButton(on);
    button == 1 ? game->Render_OptionSave(c) : game->Render_OptionLeave(c);
    game->Render_Present();
}

void Event::Option_Click(int option, int num) {
    sound->playClickSound();
    //Language option
    if (option == 1) {
        game->AddTo_LanguageOption(num);
        game->Render_OptionLanguage();
    }
    //Font option
    else if (option == 2) {
        game->AddTo_FontOption(num);
        game->Render_OptionFont();
    }
    //Music volume option
    else if (option == 3) {
        game->AddTo_MusicVolume(num);
        game->Render_OptionMusic();
    }
    //Click volume option
    else if (option == 4) {
        game->AddTo_ChunkVolume(num);
        game->Render_OptionChunk();
    }
    game->Render_Present();
}

void Event::Save_Click() {
    sound->playClickSound();
    game->Render_OptionSave(GREEN);
    game->OptionSave();
    game->Render_Option();
    sound->Set_MusicVolume(game->Get_MusicVolume());
    sound->Set_ChunkVolume(game->Get_ChunkVolume());
    sound->playSettingsSound();
    game->Render_Present();
}

void Event::Leave_Click() {
    game->Render_OptionLeave(RED);
    Option();
}

//---------------------------------------------------Display-:-More---------------------------------------------------//

void Event::Arrow_Click(int display) {
    sound->playClickSound();
    game->Reset();
    if (display == 2 || display == 5 || display == 6) {
        Start();
    }
    else if (display == 3) {
        game->Set_End(true);
        game->Set_Start(false);
        Select();
    }
    SDL_Delay(25);
}


//---------------------------------------------------Keyboard---------------------------------------------------//

void Event::Alphabetic_Keyboard(int keyType) {
    //String length is too much
    if (game->Get_Name() != "" && game->Check_NameLength(game->Get_Name() + (char)(keyType + (caps ? -32 : 0))) > 190) {
        sound->playErrorSound();
        Sleep(25);
    }
    //String is proper
    else {
        game->AddTo_Name((char)(keyType + (caps ? -32 : 0)));
        game->Render_InputField();
        game->Render_Present();
    }
}

void Event::Number_Keyboard(int keyType) {
    //String length is too much
    if (game->Get_Name() != "" && game->Check_NameLength(game->Get_Name() + (char)keyType) > 190) {
        sound->playErrorSound();
        Sleep(25);
    }
    //String is proper
    else {
        game->AddTo_Name((char)keyType);
        game->Render_InputField();
        game->Render_Present();
    }
}

void Event::Delete_Keyboard() {
    //String is empty 
    if (game->Get_Name() == "") {
        sound->playErrorSound();
        Sleep(25);
    }
    //String has at least 1 character
    else {
        game->DeleteFrom_Name();
        game->Render_InputField();
        game->Render_Present();
    }
}

void Event::Alphabetic_Keyboard_Results(int keyType) {
    //String length is too much
    if (game->Get_SearchName() != "" && game->Check_NameLength(game->Get_SearchName() + (char)(keyType + (caps ? -32 : 0))) > 190) {
        sound->playErrorSound();
        Sleep(25);
    }
    //String is proper
    else {
        game->AddTo_SearchName((char)(keyType + (caps ? -32 : 0)));
        game->Render_Results_InputField();
        game->Render_Present();
    }
}

void Event::Number_Keyboard_Results(int keyType) {
    //String length is too much
    if (game->Get_SearchName() != "" && game->Check_NameLength(game->Get_SearchName() + (char)keyType) > 190) {
        sound->playErrorSound();
        Sleep(25);
    }
    //String is proper
    else {
        game->AddTo_SearchName((char)keyType);
        game->Render_Results_InputField();
        game->Render_Present();
    }
}

void Event::Delete_Keyboard_Results() {
    //String is empty 
    if (game->Get_SearchName() == "") {
        sound->playErrorSound();
        Sleep(25);
    }
    //String has at least 1 character
    else {
        game->DelteFrom_SearchName();
        game->Render_Results_InputField();
        game->Render_Present();
    }
}
