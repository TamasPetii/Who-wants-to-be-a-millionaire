#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>

struct Player {
    std::string name = "";
    int mode;
    int time;
    int counter;
    int money;
    std::string strTime;
};

std::ostream& operator<<(std::ostream& s, Player p) {
    s << p.name << " " << p.mode << " " << p.time << " " << p.counter << " " << p.money << " " << p.strTime << std::endl;
    return s;
}

std::string Convert(int time){
    int hour = time / 3600;
	int min = time % 3600 / 60;
	int sec = time % 3600 % 60;
	return (hour < 10 ? "0" : "") + std::to_string(hour) + ":" + (min < 10 ? "0" : "") + std::to_string(min) + ":" + (sec < 10 ? "0" : "") + std::to_string(sec);
}

int main(){
    srand(time(NULL));

    std::ofstream f("Results.txt");

    if(f.fail()){
        std::cout << "Results.txt couldn't be opened!" << std::endl;
        return -1;
    }

    Player player;
    int c;
    std::vector<std::string> names = {"Peti", "Dancsi", "Pesty", "John", "Manuel", "Brendor", "TP2002", "Asd666", "Danxus23"};
    for(int i = 0; i < 150; i++){
        player.name = names[rand() % names.size()];
        player.mode = 1 + rand() % 3;
        player.counter = ((c = rand() % 16) < 10) ? rand() % 10 : c < 14 ? rand() % 14 : rand() % 16;
        player.time = 60 * player.counter + rand() % 1000;
        player.money = rand() % 2 == 0 ? player.counter : (player.counter < 5 ? 0 : player.counter < 10 ? 5 : player.counter < 15 ? 10 : 15);
        player.strTime = Convert(player.time);
        f << player;
    }
    f.close();
    return 0;
}