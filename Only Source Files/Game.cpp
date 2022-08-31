#include "Game.h"

//-----------------------------------------Init-----------------------------------------//

/*
This function is the constructor, it inits all the necessary data members. 
Including SDL window, SDL render, pictures, textures, images, colors...
*/
Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Who wants to be a millionaire?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 4);
    if (window == nullptr) throw GAME_EXCEPTION("Cannot create Window!");

    icon = IMG_Load("./pictures/icon.png");
    if (icon == nullptr) throw GAME_EXCEPTION("Cannot create Icon!");
    SDL_SetWindowIcon(window, icon);

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (render == nullptr) throw GAME_EXCEPTION("Cannot create Renderer!");

    picture = IMG_LoadTexture(render, "./pictures/Textures.png");
    if (!picture) throw GAME_EXCEPTION("Couldn't load Textures.png");

    text = new Text(render);

    Init_Images();
    Init_Colors();
    Init_Prize();
}

/*
- This function is the destructor.
- It clears all the data members of the class in order to avoid memory leak.
*/
Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_DestroyTexture(picture);
    SDL_FreeSurface(icon);

    delete text;
    images.clear();
    colors.clear();
    questions.clear();
    prize.clear();
    used.~vector();

    SDL_Quit();
}

/*
- This function containes all the positions of the objects from texture.png
*/
void Game::Init_Images() {
    images["BR"] = { 542,1768,457,139 };
    images["GR"] = { 542,1590,457,139 };
    images["RR"] = { 542,1412,457,139 };
    images["OR"] = { 542,1234,457,139 };
    images["GRR"] = { 543, 1969, 457, 139 };
    images["BS"] = { 29,1772,444,135 };
    images["GS"] = { 29, 1594, 444, 135 };
    images["RS"] = { 36,1417,444,135 };
    images["OS"] = { 36,1238,444,135 };
    images["GRS"] = { 30, 1973, 444, 135 };
    images["LOGO"] = { 0,0,810,810 };
    images["HELP1"] = { 868,482,316,244 };
    images["HELP1_X"] = { 1225, 489, 316, 244 };
    images["HELP2"] = { 880, 751, 298, 231 };
    images["HELP2_X"] = { 1234, 755, 298, 231 };
    images["HELP3"] = { 883, 997, 278, 215 };
    images["HELP3_X"] = { 1241, 1025, 278, 215 };
    images["HUN"] = { 1037, 1286, 300, 150 };
    images["HUN_X"] = { 1339, 1286, 300, 150 };
    images["GER"] = { 1037, 1438, 300, 150 };
    images["GER_X"] = { 1339, 1438, 300, 150 };
    images["ENG"] = { 1037, 1590, 300, 150 };
    images["ENG_X"] = { 1339, 1590, 300, 150 };
    images["ARROW"] = { 1042, 9,600,457 };
    images["PB_NORMAL"] = { 1211,1745,454, 752 };
    images["PB_MEDIUM"] = { 1696,0,465, 770 };
    images["PB_HARD"] = { 1699,786,454, 752 };
    images["CIRCLE"] = { 1690,1690, 810, 810 };
    images["OPTION"] = { 0, 811, 400, 419 };
    images["ARROW_L"] = { 513, 953,109,155 };
    images["ARROW_R"] = { 654, 953,109,155 };
    images["BAG"] = {111,2171,248,266};
    images["RED_X"] = { 780,2188,256,256 };
    images["GREEN_OK"] = { 472,2196,240,240 };
}

/*
- This function inits colors.
*/
void Game::Init_Colors() {
    colors[WHITE] = { 255,255,255,255 };
    colors[ORANGE] = { 255,140,0,255 };
    colors[PURPLE] = { 199,36,177, 255 };
    colors[BLACK] = { 0,0,0,255 };
}

/*
- This function reads and process the hungarian, english and german questions.
*/
void Game::Init_Questions() {
    if (!read) {
        questions[HUN] = Read(HUN);
        questions[ENG] = Read(ENG);
        questions[GER] = Read(GER);
    }
    read = true;
}

/*
- This function inits the prizes, including the prize of the normal, medium, hard game mode.
*/
void Game::Init_Prize() {
    prize[HUN] = Get_Prize(HUN);
    prize[ENG] = Get_Prize(ENG);
    prize[GER] = Get_Prize(GER);
}

/*
This function declares the different laguage and mode prizes.
*/
Pr Game::Get_Prize(Language lan) {
    if (lan == HUN) {
        return {
            { 15000000,8000000,5000000,3500000,2000000,1000000,750000,500000,300000,200000,100000,50000,35000,20000,10000 },
            { 30000000,15000000,7500000,5000000,3000000,1500000,1000000,750000,500000,300000,150000,100000,70000,40000,20000 },
            { 50000000,25000000,12500000,8000000,5000000,2500000,1500000,1000000,800000,500000,250000,150000,100000,75000,40000 }
        };
    }
    else {
        return {
            { 350000,200000,150000,120000,75000,50000,25000,12500,6000,3000,1500,950,500,200,100 },
            { 650000,350000,250000,200000,120000,75000,45000,22000,10000,5000,2250,1250,700,350,200 },
            { 1000000,500000,300000,220000,150000,100000,60000,30000,15000,7500,3500,1500,1000,500,350 }
        };
    }
}

//----------------------------------File-(Read-/-Write)----------------------------------//

/*
This function process the question text files.
It opens and sorts them by language and difficulty.
*/
Qs Game::Read(Language lan) {
    std::ifstream f(lan == HUN ? "./questions/Questions_HUN.txt" : lan == ENG ? "./questions/Questions_ENG.txt" : "./questions/Questions_GER.txt");
    if (f.fail()) {
        throw GAME_EXCEPTION("File couldn't be opened!");
    }
    line l;
    f >> l;
    std::vector<line> normal;
    std::vector<line> medium;
    std::vector<line> hard;
    while (f >> l) {
        if (atoi(l.difficulty.c_str()) <= 4) {
            normal.push_back(l);
        }
        else if (atoi(l.difficulty.c_str()) <= 8) {
            medium.push_back(l);
        }
        else {
            hard.push_back(l);
        }
    }
    f.close();
    return { normal, medium, hard };
}

/*
This function opens the Results.txt file and adds the current player game state to the file.
*/
void Game::WriteResults() {
    std::string filename("./results/Results.txt");
    std::ofstream f;

    f.open(filename, std::ios_base::app);

    if (f.fail()) {
        throw GAME_EXCEPTION("Results.txt couldn't be opened!");
    }
    f << player;
    f.close();
}

//----------------------------------Rendering-Methodes----------------------------------//

/*
This function updates the window.
*/
void Game::Render_Present() {
    SDL_RenderPresent(render);
}

/*
This function renders the MILLIONAIRE logo to the middle.
*/
void Game::Render_Logo() {
    to = { 250,25,500,500 };
    SDL_RenderCopy(render, picture, &images["LOGO"], &to);
}

/*
This functions clears the window to blue and renders the MILLIONAIRE logo to the middle.
*/
void Game::Render_Background() {
    SDL_SetRenderDrawColor(render, 19, 16, 43, 255);
    SDL_RenderClear(render);
    Render_Logo();
}

/*
This function renders an arrow to the top left of the window.
*/
void Game::Render_Arrow() {
    to = { 45, 10, 157, 120 };
    SDL_RenderCopy(render, picture, &(images["ARROW"]), &to);
}

/*
This function renders all the text on the current display.
(Mosty used when language has been changed.)
*/
void Game::Render_Texts() {
    if (display == 1) { 
        Render_StartButtons(); 
    }
    else if (display == 2) {
        Render_SelectButtons();
    }
    else if (display == 3) {
        l = Get_Line();
        Render_InGame();
    }
}

/*
This function resets all the necessary data members for other round
*/
void Game::Reset() {
    used.clear();
    l = {};
    q = -1;
    mode = 0;
    counter = 0;
    OnButton = 0;
    helps = { true, true, true };
    answer = { false, false, false, false };
    cashout = false;
}

//-----------------------------------------Start-----------------------------------------//

/*
This function renders a button with text on the START display.
x defines the button -> first = 1 | second = 2 | third = 3
c defines the color of the button
*/
void Game::Render_StartButton(int x, Colors c) {
    if(!(c == BLUE || c == ORANGE || c == GREEN)) throw GAME_EXCEPTION("Wrong Start Button Color!");

    switch (x)
    {
    case 1: // Button texted as NEW GAME
        to = { 300,540,400,75 };
        SDL_RenderCopy(render, picture, &(c == BLUE ? images["BR"] : c == ORANGE ? images["OR"] : images["GR"]), &to);
        text->Render_Text_Centered(language == HUN ? "UJ JATEK" : language == ENG ? "NEW GAME" : "NEUES SPIEL", fontType, 20, colors[WHITE], 500, 577);
        break;
    case 2: // Button texted as LEADERBOARD
        to = { 300,630,400,75 };
        SDL_RenderCopy(render, picture, &(c == BLUE ? images["BR"] : c == ORANGE ? images["OR"] : images["GR"]), &to);
        text->Render_Text_Centered(language == HUN ? "RANGLISTA" : language == ENG ? "LEADERBOARD" : "RANGLISTE", fontType, 20, colors[WHITE], 500, 667);
        break;
    case 3: // Button texted as RESULTS
        to = { 300, 720, 400, 75 };
        SDL_RenderCopy(render, picture, &(c == BLUE ? images["BR"] : c == ORANGE ? images["OR"] : images["GR"]), &to);
        text->Render_Text_Centered(language == HUN ? "EREDMENYEIM" : language == ENG ? "RESULTS" : "ERGEBNISSE", fontType, 20, colors[WHITE], 500, 757);
        break;
    default:
        throw GAME_EXCEPTION("Wrong Start Button Option!");
        break;
    }
}

/*
This function renders all the buttons at the start display as default.
*/
void Game::Render_StartButtons() {
    Render_StartButton(1, BLUE);
    Render_StartButton(2, BLUE);
    Render_StartButton(3, BLUE);
}

/*
This function renders everything on the start display.
*/
void Game::Render_Start() {
    Render_Background();
    Render_OptionImage();
    Render_StartButtons();
    Render_Present();
}


//-----------------------------------------Select-----------------------------------------//

/*
This function renders a button with text on the SELECT display.
x defines the button -> 1 = normal | 2 = medium | 3 = hard | 4 = Start game
c defines the color of the button. 
*/
void Game::Render_SelectButton(int x, Colors c) {
    if (!(c == BLUE || c == ORANGE || c == GREEN)) throw GAME_EXCEPTION("Wrong Select Button Color!");

    switch (x)
    {
    case 1: // Button texted as NORMAL
        to = { 25,540,300,75 };
        SDL_RenderCopy(render, picture, &(mode == 1 ? images["GS"] : c == BLUE ? images["BS"] : images["OS"]), &to);
        text->Render_Text_Centered("NORMAL", fontType, 20, colors[WHITE], 175, 577);
        break;
    case 2: // Button texted as MEDIUM
        to = { 350,540,300,75 };
        SDL_RenderCopy(render, picture, &(mode == 2 ? images["GS"] : c == BLUE ? images["BS"] : images["OS"]), &to);
        text->Render_Text_Centered(language == HUN ? "KOZEPES" : language == ENG ? "MEDIUM" : "MITTEL", fontType, 20, colors[WHITE], 500, 577);
        break;
    case 3: // Button texted as HARD
        to = { 675,540,300,75 };
        SDL_RenderCopy(render, picture, &(mode == 3 ? images["GS"] : c == BLUE ? images["BS"] : images["OS"]), &to);
        text->Render_Text_Centered(language == HUN ? "NEHEZ" : language == ENG ? "HARD" : "SCHWER", fontType, 20, colors[WHITE], 825, 577);
        break;
    case 4: // Button texted as START
        to = { 350,720,300,75 };
        SDL_RenderCopy(render, picture, &(c == BLUE ? images["BR"] : c == ORANGE ? images["OR"] : images["GR"]), &to);
        text->Render_Text_Centered(language == HUN ? "INDITAS" : language == ENG ? "START" : "STARTEN", fontType, 20, colors[WHITE], 500, 757);
        break;
    default:
        throw GAME_EXCEPTION("Wrong Start Button Option!");
        break;
    }
}

/*
This function renders all the buttons at the SELECT display as default.
*/
void Game::Render_SelectButtons() {
    Render_SelectButton(1, BLUE);
    Render_SelectButton(2, BLUE);
    Render_SelectButton(3, BLUE);
    Render_SelectButton(4, BLUE);
}

/*
This function renders the input text field on SELECT display.
*/
void Game::Render_InputField() {
    //Button with text
    to = { 350,630,300,75 };
    SDL_RenderCopy(render, picture, &(images["BS"]), &to);
    text->Render_Text_Centered(language == HUN ? "NEV" : language == ENG ? "NAME" : "NAME", fontType, 20, colors[WHITE], 500, 648);
    
    //White textarea
    SDL_SetRenderDrawColor(render, 255,255,255,255);
    to = { 355, 665, 290, 35 };
    SDL_RenderFillRect(render, &to);

    //Red line
    if (player.name == "") {
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderDrawLine(render, 358, 668, 358, 697);
    }
    else {
        text->Render_Text(player.name, fontType, 30, colors[BLACK], 360, 667);
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderDrawLine(render, 360 + Check_NameLength(player.name), 668, 360 + Check_NameLength(player.name), 697);
    }
}

/*
This function renders everything on SELECT display
*/
void Game::Render_Select() {
    Render_Background();
    Render_OptionImage();
    Render_SelectButtons();
    Render_InputField();
    Render_Arrow();
    Render_Present();
}

//-----------------------------------------InGame-----------------------------------------//
/*
This function renders the prize bar according to the game difficutly mode.
*/
void Game::Render_PrizeBar() {
    to = { 760, 135, 225, 400 };
    SDL_RenderCopy(render, picture, &(mode == 1 ? images["PB_NORMAL"] : mode == 2 ? images["PB_MEDIUM"] : images["PB_HARD"]), &to);
}

/*
This function renders the prizes according to the game difficulty mode and the language option.
*/
void Game::Render_PrizeTexts() {
    int c = 0;
    for (int i : (mode == 1 ? prize[language].normal : mode == 2 ? prize[language].medium : prize[language].hard)) {
        text->Render_Text(std::to_string(15 - c) + ".", fontType, 20, c % 5 == 0 ? colors[ORANGE] : colors[WHITE], 800, 147 + 25 * c);
        text->Render_Text(std::to_string(i), fontType, 20, c % 5 == 0 ? colors[ORANGE] : colors[WHITE], 840, 147 + 25 * c );
        text->Render_Text(language == HUN ? "Ft" : "$", fontType, 20, c % 5 == 0 ? colors[ORANGE] : colors[WHITE], 940, 147 + 25 * c);
        c++;
    }
}

/*
This function renders either a green or a yellow square around the prize.
The green rect means the prizes of the questions that we have achived.
The yellow rect means the current winnable prize of the question.
*/
void Game::Render_PrizeBackground() {
    //Green
    for (int i = 0; i < counter; i++) {
        SDL_SetRenderDrawColor(render, 0, 128, 0, 255);
        to = { 765, 497 - 25 * i, 215, 25 };
        SDL_RenderFillRect(render, &to);
    }
    //Yellow rect
    SDL_SetRenderDrawColor(render, 204, 204, 0, 255);
    to = { 765, 497 - 25 * (counter), 215, 25};
    SDL_RenderFillRect(render, &to);
}

/*
This function renders the while prize section.
*/
void Game::Render_Prize() {
    Render_PrizeBackground();
    Render_PrizeTexts();
    Render_PrizeBar();
}

/*
This function renders the help icons as available or as unavailable.
*/
void Game::Render_Helps() {
    //50/50
    to = { 50, 140, 180, 120 };
    SDL_RenderCopy(render, picture, &(helps.help1 ? images["HELP1"] : images["HELP1_X"]), &to);
    
    //Ask a friend
    to = { 50, 270, 180, 120 };
    SDL_RenderCopy(render, picture, &(helps.help2 ? images["HELP2"] : images["HELP2_X"]), &to);

    //Ask the crowd
    to = { 50, 400, 180, 120 };
    SDL_RenderCopy(render, picture, &(helps.help3 ? images["HELP3"] : images["HELP3_X"]), &to);
}

/*
This function renders a button with or without text on the INGAME display.
x defines the button -> 1 = A answer | 2 = B answer | 3 = c answer | 4 = D answer | 5 = Question
c defines the color of the button.
*/
void Game::Render_InGameButton(int x, Colors c) {
    if(c == WHITE || c == PURPLE) throw GAME_EXCEPTION("Wrong InGame Button Color!");
    if(q == -1) throw GAME_EXCEPTION("Couldn't find the question!");

    switch (x) {
    case 1:
        to = { 150,650,340,50 };
        SDL_RenderCopy(render, picture, &(answer.a ? images["GRR"] : c == BLUE ? images["BR"] : c == GREY ? images["GRR"] : c == GREEN ? images["GR"] : c == RED ? images["RR"] : images["OR"]), &to);
        if (!answer.a) {
            text->Render_Text("A:", fontType, 20, colors[PURPLE], 180, 665);
            text->Render_Text_Centered(l.a, fontType, 20, colors[WHITE], 320, 675);
        }
        break;
    case 2:
        to = { 510,650,340,50 };
        SDL_RenderCopy(render, picture, &(answer.b ? images["GRR"] : c == BLUE ? images["BR"] : c == GREY ? images["GRR"] : c == GREEN ? images["GR"] : c == RED ? images["RR"] : images["OR"]), &to);
        if (!answer.b) {
            text->Render_Text("B:", fontType, 20, colors[PURPLE], 540, 665);
            text->Render_Text_Centered(l.b, fontType, 20, colors[WHITE], 680, 675);
        }
        break;
    case 3:
        to = { 150,725,340,50 };
        SDL_RenderCopy(render, picture, &(answer.c ? images["GRR"] : c == BLUE ? images["BR"] : c == GREY ? images["GRR"] : c == GREEN ? images["GR"] : c == RED ? images["RR"] : images["OR"]), &to);
        if (!answer.c) {
            text->Render_Text("C:", fontType, 20, colors[PURPLE], 180, 740);
            text->Render_Text_Centered(l.c, fontType, 20, colors[WHITE], 320, 750);
        }
        break;
    case 4:
        to = { 510,725,340,50 };
        SDL_RenderCopy(render, picture, &(answer.d ? images["GRR"] : c == BLUE ? images["BR"] : c == GREY ? images["GRR"] : c == GREEN ? images["GR"] : c == RED ? images["RR"] : images["OR"]), &to);
        if (!answer.d) {
            text->Render_Text("D:", fontType, 20, colors[PURPLE], 540, 740);
            text->Render_Text_Centered(l.d, fontType, 20, colors[WHITE], 680, 750);
        }
        break;
    case 5:
        to = { 150,550,700,75 };
        SDL_RenderCopy(render, picture, &images["BS"], &to);
        if (l.question.length() > 60) {
            int half = FindHalfOfString(l.question);
            text->Render_Text_Centered(l.question.substr(0, half), fontType, 20, colors[WHITE], 500, 571);
            text->Render_Text_Centered(l.question.substr(half, l.question.length() - half), fontType, 20, colors[WHITE], 500, 598);
        }
        else {
            text->Render_Text_Centered(l.question, fontType, 20, colors[WHITE], 500, 587);
        }
        break;
    }
}

/*
This function renders the bag icon at the bottom right of the window.
*/
void Game::Render_Bag() {
    to = { 900, 700, 75, 75 };
    SDL_RenderCopy(render, picture, &(images["BAG"]), &to);
}

/*
This function renders all the buttons on InGame display.
*/
void Game::Render_InGameButtons() {
    Render_InGameButton(5, BLUE);
    Render_InGameButton(1, BLUE);
    Render_InGameButton(2, BLUE);
    Render_InGameButton(3, BLUE);
    Render_InGameButton(4, BLUE);
}

/*
After you click on the bag icon this function is going to render the current winnable prize.
*/
void Game::Render_CashOut() {
    SDL_SetRenderDrawColor(render, 19, 16, 43, 255);
    to = { 250,25,500,500 };
    SDL_RenderFillRect(render, &to);
    if (!cashout) {
        SDL_RenderCopy(render, picture, &images["CIRCLE"], &to);

        SDL_SetRenderDrawColor(render, 19, 16, 143, 255);
        to = { 350, 175, 300, 200 };
        SDL_RenderFillRect(render, &to);


        text->Render_Text_Centered(language == HUN ? "NYEREMENY" : language == ENG ? "PRIZE" : "GEWINN", fontType, 30, colors[WHITE], 500, 200);
        
        std::string str = "";

        if (counter == 0) {
            text->Render_Text_Centered(str.append("0").append(language == HUN ? " Ft" : " $"), fontType, 50, colors[ORANGE], 500, 275);
        }
        else {
            text->Render_Text_Centered(str.append(std::to_string(mode == 1 ? prize[language].normal[15 - counter] : mode == 2 ? prize[language].medium[15 - counter] : prize[language].hard[15 - counter])).append(language == HUN ? " Ft" : " $"), fontType, 50, colors[ORANGE], 500, 275);
        }
        to = { 355,320, 50, 50 };
        SDL_RenderCopy(render, picture, &images["GREEN_OK"], &to);

        to = { 595,320, 50, 50 };
        SDL_RenderCopy(render, picture, &images["RED_X"], &to);
        cashout = true;
    }
    else {
        SDL_RenderCopy(render, picture, &images["LOGO"], &to);
        cashout = false;
    }
    Render_Present();
}

/*
After you lost a game or answered all the 15 questions this function will render the money that you won.
*/
void Game::Render_FixCashOut() {
    SDL_SetRenderDrawColor(render, 19, 16, 43, 255);
    to = { 250,25,500,500 };
    SDL_RenderFillRect(render, &to);

    SDL_RenderCopy(render, picture, &images["CIRCLE"], &to);

    SDL_SetRenderDrawColor(render, 19, 16, 143, 255);
    to = { 350, 175, 300, 200 };
    SDL_RenderFillRect(render, &to);

    text->Render_Text_Centered("NYEREMENY", fontType, 30, colors[WHITE], 500, 200);

    std::string str = "";

    if (fixMoney == 0) {
        text->Render_Text_Centered(str.append("0").append(language == HUN ? " Ft" : " $"), fontType, 50, colors[ORANGE], 500, 275);
    }
    else {
        text->Render_Text_Centered(str.append(std::to_string(mode == 1 ? prize[language].normal[15 - fixMoney * 5] : mode == 2 ? prize[language].medium[15 - fixMoney * 5] : prize[language].hard[15 - fixMoney * 5])).append(language == HUN ? " Ft" : " $"), fontType, 50, colors[ORANGE], 500, 275);
    }

    Render_Present();
}

/*
This function renders the whole INGAME display
*/
void Game::Render_InGame() {
    Render_Background();
    Render_OptionImage();
    Render_Arrow();
    Render_Helps();
    Render_Prize();
    Render_InGameButtons();
    Render_Bag();
    Render_Present();
}

//-------------------------------------------------Render-Option--------------------------------------------------//

/*
# What it does? 
- This function renders the settings logo to the top right corner of the window.
*/
void Game::Render_OptionImage() {
    to = { 835, 5, 125, 125 };
    SDL_RenderCopy(render, picture, &(images["OPTION"]), &to);
}

/*
# What it does?
- This function clears the window to blue and renders the "Setting" text to the top of the screen.
*/
void Game::Render_OptionSetting() {
    SDL_SetRenderDrawColor(render, 19, 16, 43, 255);
    SDL_RenderClear(render);

    text->Render_Text_Centered(language == HUN ? "Beallitasok" : language == ENG ? "Settings" : "Einstellung", fontType, 140, colors[ORANGE], 500, 90);
}

/*
# What it does?
- This function renders the language option.
# Render includes
- Light blue rect behind the texts
- Language as a text
- Left and Right blue arrows
- The chosen language as a text and after its flag
*/
void Game::Render_OptionLanguage() {
    SDL_SetRenderDrawColor(render, 19, 16, 143, 255);
    to = { 200, 195, 600, 50 };
    SDL_RenderFillRect(render, &to);

    text->Render_Text(language == HUN ? "Nyelv:" : language == ENG ? "Language:" : "Sprache:", fontType, 35, colors[WHITE], 210, 200);

    if (options.languageOption % 3 == 0) {
        text->Render_Text_Centered(language == HUN ? "Magyar" : language == ENG ? "Hungarian" : "Ungarisch", fontType, 30, colors[WHITE], 613, 222);

        to = { 690, 210, 50, 25 };
        SDL_RenderCopy(render, picture, &(images["HUN"]), &to);
    }
    else if (options.languageOption % 3 == 1) {
        text->Render_Text_Centered(language == HUN ? "Angol" : language == ENG ? "English" : "Englisch", fontType, 30, colors[WHITE], 613, 222);

        to = { 690, 210, 50, 25 };
        SDL_RenderCopy(render, picture, &(images["ENG"]), &to);
    }
    else if (options.languageOption % 3 == 2) {
        text->Render_Text_Centered(language == HUN ? "Nemet" : language == ENG ? "German" : "Deutsch", fontType, 30, colors[WHITE], 613, 222);

        to = { 690, 210, 50, 25 };
        SDL_RenderCopy(render, picture, &(images["GER"]), &to);
    }

    to = { 510, 210, 25, 25 };
    SDL_RenderCopy(render, picture, &(images["ARROW_L"]), &to);

    to = { 750, 210, 25, 25 };
    SDL_RenderCopy(render, picture, &(images["ARROW_R"]), &to);
}

/*
# What it does?
- This function renders the font option.
# Render includes
- Light blue rect behind the texts
- Font as a text
- Left and Right blue arrows
- The chosen font type as a text
*/
void Game::Render_OptionFont() {

    SDL_SetRenderDrawColor(render, 19, 16, 143, 255);
    to = { 200, 255, 600, 50 };
    SDL_RenderFillRect(render, &to);

    text->Render_Text(language == HUN ? "Betutipus:" : language == ENG ? "Font:" : "Schriftart:", fontType, 35, colors[WHITE], 210, 260);

    if (options.typeOption % 3 == 0) {
        text->Render_Text_Centered("Times New R.", fontType, 30, colors[WHITE], 643, 282);
    }
    else if (options.typeOption % 3 == 1) {
        text->Render_Text_Centered("Minecraft", fontType, 30, colors[WHITE], 643, 282);
    }
    else if (options.typeOption % 3 == 2) {
        text->Render_Text_Centered("IndieFlower", fontType, 30, colors[WHITE], 643, 282);
    }

    to = { 510, 270, 25, 25 };
    SDL_RenderCopy(render, picture, &(images["ARROW_L"]), &to);

    to = { 750, 270, 25, 25 };
    SDL_RenderCopy(render, picture, &(images["ARROW_R"]), &to);
}

/*
# What it does?
- This function renders the Music option.
# Render includes
- Light blue rect behind the texts
- Music Volmue as a text
- Left and Right blue arrows
- The chosen Music Volume on a scale from 0 to 10
*/
void Game::Render_OptionMusic() {
    SDL_SetRenderDrawColor(render, 19, 16, 143, 255);
    to = { 200, 315, 600, 50 };
    SDL_RenderFillRect(render, &to);

    text->Render_Text(language == HUN ? "ZeneHangero:" : language == ENG ? "MusicVolume:" : "MusikVolumen:", fontType, 35, colors[WHITE], 210, 320);

    text->Render_Text_Centered(std::to_string(options.musicVolume % 11), fontType, 30, colors[WHITE], 643, 342);

    to = { 510, 330, 25, 25 };
    SDL_RenderCopy(render, picture, &(images["ARROW_L"]), &to);

    to = { 750, 330, 25, 25 };
    SDL_RenderCopy(render, picture, &(images["ARROW_R"]), &to);
}

/*
# What it does?
- This function renders the Chunk (ClickSound) option.
# Render includes
- Light blue rect behind the texts
- Click Volmue as a text
- Left and Right blue arrows
- The chosen Chunk Volume on a scale from 0 to 10
*/
void Game::Render_OptionChunk() {
    SDL_SetRenderDrawColor(render, 19, 16, 143, 255);
    to = { 200, 375, 600, 50 };
    SDL_RenderFillRect(render, &to);

    text->Render_Text(language == HUN ? "KlikkHangero:" : language == ENG ? "ClickVolume:" : "KlickVolumen:", fontType, 35, colors[WHITE], 210, 380);
    
    text->Render_Text_Centered(std::to_string(options.chunkVolume % 11), fontType, 30, colors[WHITE], 643, 402);

    to = { 510, 390, 25, 25 };
    SDL_RenderCopy(render, picture, &(images["ARROW_L"]), &to);

    to = { 750, 390, 25, 25 };
    SDL_RenderCopy(render, picture, &(images["ARROW_R"]), &to);
}

/*
# What it does?
- This function renders either a green button or orange button labeled as SAVE.
*/
void Game::Render_OptionSave(Colors c) {
    to = { 300,600,400,75 };
    SDL_RenderCopy(render, picture, &(c == ORANGE ? images["OR"] : images["GR"]), &to);
    text->Render_Text_Centered(language == HUN ? "MENTES" : language == ENG ? "SAVE" : "SPEICHERN", fontType, 25, colors[WHITE], 500, 637);
}

/*
# What it does?
- This function renders either a red button or orange button labeled as LEAVE.
*/
void Game::Render_OptionLeave(Colors c) {
    to = { 300,700,400,75 };
    SDL_RenderCopy(render, picture, &(c == ORANGE ? images["OR"] : images["RR"]), &to);
    text->Render_Text_Centered(language == HUN ? "KILEPES" : language == ENG ? "LEAVE" : "VERLASSEN", fontType, 25, colors[WHITE], 500, 737);
}

/*
# What it does?
- This function sets the language and font parameteres after the user clicked on the save button.
*/
void Game::OptionSave() {
    options.languageOption % 3 == 0 ? language = HUN : options.languageOption % 3 == 1 ? language = ENG : language = GER;
    fontType = options.typeOption % 3;
}
/*
# What it does?
- This function renders the whole option screen.
*/
void Game::Render_Option() {
    Render_OptionSetting();
    Render_OptionImage();
    Render_OptionFont();
    Render_OptionLanguage();
    Render_OptionMusic();
    Render_OptionChunk();
    Render_OptionSave(GREEN);
    Render_OptionLeave(RED);
    Render_Present();
}

//---------------------------Render-Helps-----------------------------//

/*
This is the help 50/50.
The function gives RANDOMLY to numbers which can not be the answer.
Those 2 numbers will be the eleminated from the possible answers.
*/
void Game::Start_Help1() {
    int x1, x2;
    int a = l.answer == "A" ? 1 : l.answer == "B" ? 2 : l.answer == "C" ? 3 : 4;
    do {
        x1 = Random(1, 4);
    } while (x1 == a);
    do {
        x2 = Random(1, 4);
    } while (x2 == a || x2 == x1);
    
    if (x1 == 1 || x2 == 1) {
        answer.a = true;
    }
    if (x1 == 2 || x2 == 2) {
        answer.b = true;
    }
    if (x1 == 3 || x2 == 3) {
        answer.c = true;
    }
    if (x1 == 4 || x2 == 4) {
        answer.d = true;
    }
    Render_InGameButtons();
    Render_Present();
}

/*
This function renders the the LOGO with a transparent center.
It renders the available time for speaking in the center.
*/
void Game::Render_Help2(int x, bool help) {
    SDL_SetRenderDrawColor(render, 19, 16, 43, 255);
    to = { 250,25,500,500 };
    SDL_RenderFillRect(render, &to);
    if (help) {
        SDL_RenderCopy(render, picture, &images["CIRCLE"], &to);
        text->Render_Text_Centered(std::to_string(x), fontType, 250, colors[WHITE], 500, 275);
    }
    else {
        SDL_RenderCopy(render, picture, &images["LOGO"], &to);
    }
    Render_Present();
}

/*
This funtion is the PHONE A FRIEND help.
*/
void Game::Start_Help2() {
    int c = 30;
    while (c != -1) {
        Render_Help2(c--, true);
        if(c != 0) Sleep(1000);
    }
    for (int i = 0; i < 4; i++) {
        Render_Help2(0, true);
        Sleep(100);  
        Render_Help2(0, false);
        Sleep(100);
    }
}

/*
This function renders the CROWD help.
It renders the coordinate system, the alphabets, the precenteges and the logo with a transparent center.
*/
void Game::Render_Help3() {
    SDL_SetRenderDrawColor(render, 19, 16, 43, 255);
    to = { 250,25,500,500 };
    SDL_RenderFillRect(render, &to);
    SDL_RenderCopy(render, picture, &images["CIRCLE"], &to);

    SDL_SetRenderDrawColor(render, 82, 192, 243, 255);

    for (int i = 0; i < 10; i++) {
        to = { 400 + i * 20, 175, 2, 200 };
        SDL_RenderFillRect(render, &to);

        to = { 400, 175 + i * 20, 200, 2 };
        SDL_RenderFillRect(render, &to);
    }

    to = { 598, 175, 2, 200 };
    SDL_RenderFillRect(render, &to);

    to = { 400, 373, 200, 2 };
    SDL_RenderFillRect(render, &to);

    text->Render_Text("A", fontType, 20, colors[ORANGE], 405, 380);
    text->Render_Text("B", fontType, 20, colors[ORANGE], 463, 380);
    text->Render_Text("C", fontType, 20, colors[ORANGE], 521, 380);
    text->Render_Text("D", fontType, 20, colors[ORANGE], 580, 380);
}

/*
This function is an animation while the crowd votes.
Technically it gives 4 random number and renders it into the coordinate system.
*/
void Game::Render_Precentage(int x1, int x2, int x3, int x4) {
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    to = { 400, 375, 25, -x1 * 2 };
    SDL_RenderFillRect(render, &to);
    text->Render_Text(std::to_string(x1) + "%", fontType, 20, colors[ORANGE], 400, 155);

    to = { 458, 375, 25, -x2 * 2};
    SDL_RenderFillRect(render, &to);
    text->Render_Text(std::to_string(x2) + "%", fontType, 20, colors[ORANGE], 458, 155);

    to = { 516, 375, 25, -x3 * 2};
    SDL_RenderFillRect(render, &to);
    text->Render_Text(std::to_string(x3) + "%", fontType, 20, colors[ORANGE], 516, 155);

    to = { 575, 375, 25, -x4 * 2};
    SDL_RenderFillRect(render, &to);
    text->Render_Text(std::to_string(x4) + "%", fontType, 20, colors[ORANGE], 575, 155);
}

/*
This function is the ASK THE CROWD help.
First it does the voting animation then it gives 4 random number.
Most of the time the right answer is the highest number but not all the time.
*/
void Game::Start_Help3() {
    for (int i = 0; i < 90; i++) {
        Render_Help3();
        Render_Precentage(Random(0, 100), Random(0, 100), Random(0, 100), Random(0, 100));
        Render_Present();
        Sleep(100);
    }
    int x1, x2, x3, x4;
    x1 = 40 + Random(0, 50);
    do {
        x2 = Random(0, x1);
    } while (x1 + x2 > 100);
    do {
        x3 = Random(0, x2);
    } while (x1 + x2 + x3 > 100);
    x4 = 100 - x1 - x2 - x3;
    Render_Help3();
    if (l.answer == "A") {
        Render_Precentage(x1, x2, x3, x4);
    }
    else if (l.answer == "B") {
        Render_Precentage(x2, x1, x3, x4);
    }
    else if (l.answer == "C") {
        Render_Precentage(x2, x3, x1, x4);
    }
    else {
        Render_Precentage(x2, x3, x4, x1);
    }
    Render_Present();
}

//-----------------------------Leaderboard-------------------------------//

/*
This function renders the background of the LeaderBoard display (The rects).
x defines the column : x = 1 -> First column | x = 2 -> Second column | x = 3 -> Third column
*/
void Game::Render_LB_BG(int x) {
    for (int i = 0; i < 10; i++) {
        to = { 25 + x * 325, 225 + i * 55, 300, 50 };
        if (i == 0) {
            SDL_SetRenderDrawColor(render, 187, 161, 79, 255);
            SDL_RenderFillRect(render, &to);
        }
        else if (i == 1) {
            SDL_SetRenderDrawColor(render, 107,107,107, 255);
            SDL_RenderFillRect(render, &to);
        }
        else if (i == 2) {
            SDL_SetRenderDrawColor(render, 191, 137, 112, 255);
            SDL_RenderFillRect(render, &to);
        }
        else {
            SDL_SetRenderDrawColor(render, 19, 16, 143, 255);
            SDL_RenderFillRect(render, &to);
        }
    }
}

/*
This function renders the texts on the LeaderBoard Display.
*/
void Game::Render_LB_HelpTexts() {
    text->Render_Text_Centered(language == HUN ? "(NEV | JO VALASZOK | IDO)" : language == ENG ? "(NAME, GOOD ANSWERS, TIME)" : "(NAME, GUTE ANTWORTEN, ZEIT)", fontType, 35, colors[WHITE], 500, 75);
    text->Render_Text_Centered("NORMAL", fontType, 35, colors[ORANGE], 175, 200);
    text->Render_Text_Centered(language == HUN ? "KOZEPES" : language == ENG ? "MEDIUM" : "MITTEL", fontType, 35, colors[ORANGE], 500, 200);
    text->Render_Text_Centered(language == HUN ? "NEHEZ" : language == ENG ? "HARD" : "SCHWER", fontType, 35, colors[ORANGE], 825, 200);
}

/*
This function sorts the vectors.
*/
void Game::Sort_Vec(std::vector<Player>& vec) {
    Sort_Players(vec, 1);
    Sort_Players(vec, 3);
}

/*
This function swaps to element in a vector.
*/
void Game::Swap(Player& x, Player& y) {
    Player temp = x;
    x = y;
    y = temp;
}

/*
This function is a maximum selection sort.
The option defines the value according to which we will sort the vector.
*/
void Game::Sort_Players(std::vector<Player>& vec, int option) {
    int n = vec.size() - 1;
    for (unsigned int i = n; i >= 1; i--) {
        int ind = 0;
        for (unsigned int j = 1; j <= i; j++) {
            if ((option == 1 ? (vec[j].time <= vec[ind].time) : option == 2 ? (vec[j].money >= vec[ind].money) : (vec[j].counter >= vec[ind].counter))) {
                ind = j;
            }
        }
        Swap(vec[ind], vec[i]);
    }
}

/*
This function opens the Results.txt and process it.
It sorts the vectors and displays the first 10 player on the LeaderBoard
*/
void Game::Render_LB_Players() {
    std::ifstream f("./results/Results.txt");

    if (f.fail()) {
        throw GAME_EXCEPTION("Results.txt couldn't be opened!");
    }

    std::vector<Player> players_normal;
    std::vector<Player> players_medium;
    std::vector<Player> players_hard;
    Player player;
    while (f >> player) {
        if (player.mode == 1) {
            players_normal.push_back(player);
        }
        else if (player.mode == 2) {
            players_medium.push_back(player);
        }
        else {
            players_hard.push_back(player);
        }
    }

    if (players_normal.size() >= 2) Sort_Vec(players_normal);
    if (players_medium.size() >= 2)Sort_Vec(players_medium);
    if (players_hard.size() >= 2)Sort_Vec(players_hard);

    Render_LB_PlayerText(players_normal, 0);
    Render_LB_PlayerText(players_medium, 1);
    Render_LB_PlayerText(players_hard, 2);

    players_normal.clear();
    players_medium.clear(); 
    players_hard.clear();
}

/*
This function displayer the first 10 player on the leaderboard
*/
void Game::Render_LB_PlayerText(std::vector<Player> vec, int mode) {
    int n = (vec.size() < 10 ? vec.size(): 10);
    for (int i = 0; i < n; i++) {
        text->Render_Text_YCentered(vec[vec.size() - 1 - i].name, fontType, 20, colors[WHITE], 30 + mode * 325, 250 + i * 55);
        text->Render_Text_YCentered(std::to_string(vec[vec.size() - 1 - i].counter), fontType, 20, colors[WHITE], 175 + mode * 325, 250 + i * 55);
        text->Render_Text_YCentered(vec[vec.size() - 1 - i].strTime, fontType, 20, colors[WHITE], 245 + mode * 325, 250 + i * 55);
    }
}

/*
This function renders all the texts that can be found on the Leaderboard display
*/
void Game::Render_LB_Texts() {
    Render_LB_HelpTexts();
    Render_LB_Players();
}

/*
This function renders the normal, medium, hard backgound.
*/
void Game::Render_LB_BackGround() {
    Render_LB_BG(0);
    Render_LB_BG(1);
    Render_LB_BG(2);
}

/*
This function renders everything on the LeaderBoard display.
*/
void Game::Render_Leaderboards() {
    SDL_SetRenderDrawColor(render, 19, 16, 43, 255);
    SDL_RenderClear(render);
    Render_Arrow();
    Render_OptionImage();
    Render_LB_BackGround();
    Render_LB_Texts();
    Render_Present();
}

//-------------------------------------Results--------------------------------------//

/*
This function renders everything on the Results display
*/
void Game::Render_Results() {
    SDL_SetRenderDrawColor(render, 19, 16, 43, 255);
    SDL_RenderClear(render);
    Render_Arrow();
    Render_OptionImage();
    Render_Results_Texts();
    Render_Results_InputField();
    Render_Present();
}

/*
This function opens the Results.txt and process it.
It finds all the game ending according to the given player name.
After sorting the game endings of the player it renders them as a text.
*/
void Game::Render_Results_Player() {
    std::ifstream f("./results/Results.txt");

    if (f.fail()) {
        throw GAME_EXCEPTION("Results.txt couldn't be opened!");
    }

    std::vector<Player> players_normal;
    std::vector<Player> players_medium;
    std::vector<Player> players_hard;

    Player player;
    while (f >> player) {
        if (player.mode == 1 && player.name == searchName) {
            players_normal.push_back(player);
        }
        else if (player.mode == 2 && player.name == searchName) {
            players_medium.push_back(player);
        }
        else if(player.mode == 3 && player.name == searchName) {
            players_hard.push_back(player);
        }
    }

    if (players_normal.size() >= 2) Sort_Vec(players_normal);
    if (players_medium.size() >= 2)Sort_Vec(players_medium);
    if (players_hard.size() >= 2)Sort_Vec(players_hard);

    Render_LB_PlayerText(players_normal, 0);
    Render_LB_PlayerText(players_medium, 1);
    Render_LB_PlayerText(players_hard, 2);

    players_normal.clear();
    players_medium.clear();
    players_hard.clear();
}

/*
This function renders the background and all the texts that are on the Results display.
*/
void Game::Render_Results_Texts() {
    Render_LB_BackGround();
    Render_Results_HelpTexts();
    Render_Results_Player();
}

/*
This function renders the input filed including the button, the button text and the white input field.
*/
void Game::Render_Results_InputField() {
    //Button with text
    to = { 350,30,300,75 };
    SDL_RenderCopy(render, picture, &(images["BS"]), &to);
    text->Render_Text_Centered(language == HUN ? "NEV KERESESE" : language == ENG ? "SEARCH NAME" : "SUCHE NAME", fontType, 20, colors[WHITE], 500, 48);

    //White textarea
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    to = { 355, 65, 240, 35 };
    SDL_RenderFillRect(render, &to);

    //Green ok
    to = { 605, 65, 35, 35 };
    SDL_RenderCopy(render, picture, &images["GREEN_OK"], &to);

    //Red line
    if (searchName == "") {
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderDrawLine(render, 358, 68, 358, 97);
    }
    else {
        text->Render_Text(searchName, fontType, 30, colors[BLACK], 360, 67);
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderDrawLine(render, 360 + Check_NameLength(searchName), 68, 360 + Check_NameLength(searchName), 97);
    }
}

/*
This function renders texts on the Results display
*/
void Game::Render_Results_HelpTexts() {
    text->Render_Text_Centered(language == HUN ? "(NEV | JO VALASZOK | IDO)" : language == ENG ? "(NAME, GOOD ANSWERS, TIME)" : "(NAME, GUTE ANTWORTEN, ZEIT)", fontType, 35, colors[WHITE], 500, 150);
    text->Render_Text_Centered("NORMAL", fontType, 35, colors[ORANGE], 175, 200);
    text->Render_Text_Centered(language == HUN ? "KOZEPES" : language == ENG ? "MEDIUM" : "MITTEL", fontType, 35, colors[ORANGE], 500, 200);
    text->Render_Text_Centered(language == HUN ? "NEHEZ" : language == ENG ? "HARD" : "SCHWER", fontType, 35, colors[ORANGE], 825, 200);
}


//---------------------------Other-Helping-Methodes---------------------------//

/*
This function gives a random question and renders on the INGAME display.
*/
void Game::Get_Question() {
    if (counter < 15) {
        Get_RandomQuestion();
        Render_InGame();
    }
}
/*
This function generates a random question, checks if its leagal and sets the proper data members.
*/
void Game::Get_RandomQuestion() {
    int to = (mode == 1 ? questions[HUN].normal.size() : mode == 2 ? questions[HUN].medium.size() : questions[HUN].hard.size());
    do {
        q = Random(0, to);
    } while (AlreadyUsed());
    used.push_back(q);
    l = Get_Line();
}

/*
This function checks if the question is already used.
*/
bool Game::AlreadyUsed() {
    bool l = false;
    for (unsigned int i = 0; i < used.size() && !l; i++) {
        l = l || q == used[i];
    }
    return l;
}

/*
This function gives a random number (from - to)
*/
int Game::Random(int from, int to) {
    return from + rand() % (to - from);
}

/*
This function returns the question according to the current language setting
*/
line Game::Get_Line() {
    return (mode == 1 ? questions[language].normal[q] : mode == 2 ? questions[language].medium[q] : questions[language].hard[q]);
}

/*
This function find the half of the string. 
It is used when we renders the question in order to not reach out of the button
*/
int Game::FindHalfOfString(std::string str) {
    int ind = 0;
    for (int i = 0; i < 60; i++) {
        if (str[i] == ' ') {
            ind = i;
        }
    }
    return ind;
}

/*
This function checks if the given question answer is equal to the question answer.
*/
bool Game::Answer(std::string str) {
    return str == l.answer;
}

/*
This function returns the question answer as an integer
(A = 1 | B = 2 | C = 3 | D = 4)
*/
int Game::Get_GoodAnswerNum() {
    return (l.answer == "A" ? 1 : l.answer == "B" ? 2 : l.answer == "C" ? 3 : 4);
}

/*
This function returns the length of a text surface.
*/
int Game::Check_NameLength(std::string str) {
    return text->Check_Length(str, fontType, 30);
}

/*
This function sets the fix money that a player can win.
*/
void Game::Set_FixMoney() {
    if (counter % 5 == 0) {
        fixMoney++;
    }
}