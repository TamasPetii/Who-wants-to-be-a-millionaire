#include "Structures.h"

std::ostream& operator<<(std::ostream& s, line l) {
    s << l.difficulty << " " << l.question << " " << l.a << " " << l.b << " " << l.c << " " << l.d << " " << l.answer << " " << l.category << std::endl;
    return s;
}

std::istream& operator>>(std::istream& s, line& l) {
    getline(s, l.difficulty, '\t');
    getline(s, l.question, '\t');
    getline(s, l.a, '\t');
    getline(s, l.b, '\t');
    getline(s, l.c, '\t');
    getline(s, l.d, '\t');
    getline(s, l.answer, '\t');
    getline(s, l.category, '\n');
    return s;
}

std::ostream& operator<<(std::ostream& s, Player p) {
    s << p.name << " " << p.mode << " " << p.time << " " << p.counter << " " << p.money << " " << p.strTime << std::endl;
    return s;
}

std::istream& operator>>(std::istream& s, Player& p) {
    s >> p.name >> p.mode >> p.time >> p.counter >> p.money >> p.strTime;
    return s;
}