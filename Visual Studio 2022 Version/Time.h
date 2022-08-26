#pragma once
#include <string>

class Time
{
private:
	int secundum = 0;
public:
	Time() {}

	void Reset() { secundum = 0; }
	void Count() { secundum++; }
	int Get_Sec() { return secundum; }
	std::string To_String();
};